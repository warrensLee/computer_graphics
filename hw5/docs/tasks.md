# HW5 – Implementation Plan
## Features 1, 2, and 3

**Due: Friday April 24th, 2026 at 11:59pm**

---

## OOP Directory Contract

| Directory | Owns |
|-----------|------|
| `core/` | Math primitives, shared constants — `ray_classes.h/cpp`, `config.h` |
| `model/` | Scene data and ray tracing engine — `raytracer.h/cpp`, `scene.h/cpp`, objects |
| `view/` | OpenGL rendering only — `render.h/cpp`, `camera.h/cpp` |
| `app/` | GLUT entry point, callbacks — `app.h/cpp`, `main.cpp` |
| `controller/` | Input handling — `controller.h/cpp` |

---

## Step 0 – Wire RayTracer into the App (Prerequisite)

**Goal:** Connect the already-written `RayTracer` class into the OpenGL display pipeline so the ray-traced image buffer actually appears on screen. No feature logic changes — just wiring and build fixes.

**Why this is needed:** `render.h` currently declares `RayTracer& tracer` as a reference member alongside `Render() = default`. A reference member cannot be default-constructed — this is a compile error. The `RayTracer` is also missing from both `App` and the `Makefile`, so the project cannot link as-is.

---

### Step 0.1 — Fix `render.h`
**File:** `view/render.h`

**Problem:** `RayTracer& tracer` is a reference member but `Render() = default` cannot initialize it. The reference is also never read anywhere in `render.cpp`.

**Change:** Remove `RayTracer& tracer`, remove the unused `Render(RayTracer& rayTracer)` constructor declaration, remove the `#include "../model/raytracer.h"` include, and add one new method declaration:

```cpp
void drawRayTracedImage(const unsigned char* buf, int w, int h);
```

The `Render() = default` constructor stays as-is.

---

### Step 0.2 — Fix `render.cpp`
**File:** `view/render.cpp`

**Problem:** `Render::Render(RayTracer& rayTracer) : tracer(rayTracer) {}` is the only non-default constructor defined; it must be removed now that the reference member is gone.

**Change:** Delete that constructor body. Add the implementation of `drawRayTracedImage`:

```cpp
void Render::drawRayTracedImage(const unsigned char* buf, int w, int h)
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // glDrawPixels reads bottom-to-top; flip so image[0] is the top row
    glPixelZoom(1.0f, -1.0f);
    glRasterPos2i(0, h);
    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, buf);
    glPixelZoom(1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}
```

Everything else in `render.cpp` stays identical.

---

### Step 0.3 — Add `RayTracer` to `app.h`
**File:** `app/app.h`

**Change:** Add `#include "../model/raytracer.h"` and add `RayTracer rayTracer` as a private member alongside `renderer`, `controller`, and `scene`.

No other changes to `app.h`.

---

### Step 0.4 — Wire display and idle in `app.cpp`
**File:** `app/app.cpp`

Two small changes:

**In `App::display()`** — after the `glClear` call, replace `renderer.draw(scene)` with a call that blits the ray-traced image, then keeps the text overlay:

```cpp
// replace renderer.draw(scene) with:
renderer.drawRayTracedImage(rayTracer.getImageBuffer(), Config::XDIM, Config::YDIM);
```

**In `App::idle()`** — add one line before `glutPostRedisplay()`:

```cpp
rayTracer.traceScene();   // re-render ray traced image each frame
```

The delta-time calculation and `scene.update(dt)` stay in place for future use.

---

### Step 0.5 — Update `Makefile`
**File:** `Makefile`

**Change:** Add `core/ray_classes.o` and `model/raytracer.o` to the `OBJS` list so they compile and link. This is the only Makefile change needed for all three features.

Current OBJS line:
```makefile
OBJS = app/main.o app/app.o \
       model/texture.o model/scene.o model/object3D.o model/sphereObject.o model/cubeObject.o \
       controller/controller.o \
       view/render.o view/camera.o
```

New OBJS line:
```makefile
OBJS = app/main.o app/app.o \
       core/ray_classes.o \
       model/raytracer.o model/texture.o model/scene.o model/object3D.o model/sphereObject.o model/cubeObject.o \
       controller/controller.o \
       view/render.o view/camera.o
```

**Checkpoint after Step 0:** `make` compiles clean. Window opens and shows a single pink/red Phong-shaded sphere on a black background (the existing `traceScene()` output).

---

## Feature 1 – Turner Whitted's Sphere Animation

**Goal:** A solid yellow ball orbiting a stationary grey ball over a red/yellow checkerboard floor, updating every frame.

### Step 1.1 — Add `Plane3D` to ray classes
**File:** `core/ray_classes.h` and `core/ray_classes.cpp`

Add a `Plane3D` class alongside `Sphere3D`. Defined by a point on the plane, a surface normal, and two checkerboard colors.

```cpp
// In ray_classes.h — add after Sphere3D
class Plane3D
{
 public:
   Point3D  point;
   Vector3D normal;
   ColorRGB color1, color2;
   float    tileSize;

   void set(Point3D p, Vector3D n, ColorRGB c1, ColorRGB c2, float tile);
   bool get_intersection(Ray3D ray, Point3D &hitPoint, Vector3D &hitNormal);
   ColorRGB get_checker_color(Point3D hitPoint);
};
```

In `ray_classes.cpp`, implement `get_intersection` using the standard formula:
`t = dot(point - ray.point, normal) / dot(ray.dir, normal)`.
Return `false` if `|denominator| < 1e-6` (parallel) or `t < 0.001` (behind camera).

Implement `get_checker_color` by computing `int(floor(hitPoint.px / tileSize)) + int(floor(hitPoint.pz / tileSize))` and returning `color1` if the sum is even, `color2` if odd.

---

### Step 1.2 — Add color and material fields to `Sphere3D`
**File:** `core/ray_classes.h`

Add two fields to the existing `Sphere3D` class:
```cpp
ColorRGB color;
float    Ks;      // reflection coefficient (0 = no reflection)
```

These default to zero-initialized, so all existing code calling `sphere.set(center, radius)` continues to work. After calling `set()`, callers set the color/Ks manually.

---

### Step 1.3 — Add animation state to `RayTracer`
**File:** `model/raytracer.h` and `model/raytracer.cpp`

In `raytracer.h`, add these members to `RayTracer`:
```cpp
Sphere3D stationarySphere;
Sphere3D movingSphere;
Plane3D  floorPlane;
float    orbitAngle;
float    orbitRadius;
```

In the constructor (`raytracer.cpp`), initialize:
- `stationarySphere` centered at (0, 0, 3), radius 1.5, color grey (180, 180, 180), Ks 0.0
- `movingSphere` radius 0.8, color yellow (230, 200, 0), Ks 0.0
- `floorPlane` at point (0, -2, 0), normal (0, 1, 0), color1 red (200, 50, 50), color2 yellow (230, 200, 0), tileSize 1.5
- `orbitAngle = 0.0f`, `orbitRadius = 3.0f`

Add a `void step(float dt)` method declaration in `raytracer.h` and implement it in `raytracer.cpp`:
```cpp
void RayTracer::step(float dt)
{
    orbitAngle += dt * 1.2f;
    movingSphere.center.px = orbitRadius * cos(orbitAngle);
    movingSphere.center.py = -0.5f + sin(orbitAngle * 2.0f) * 0.5f;
    movingSphere.center.pz = 3.0f + orbitRadius * sin(orbitAngle);
}
```

---

### Step 1.4 — Rewrite `traceScene()` for the Whitted scene
**File:** `model/raytracer.cpp`

Replace the body of `traceScene()`. Keep all variable names and patterns identical to the original — add the floor and second sphere alongside the existing sphere logic:

```cpp
void RayTracer::traceScene()
{
    Phong shader;

    Point3D camera;
    camera.set(0, 0, -position);
    shader.SetCamera(camera);

    ColorRGB lightColor;
    lightColor.set(255, 255, 255);
    Vector3D lightDir;
    lightDir.set(-1, -1, -1);
    lightDir.normalize();
    shader.SetLight(lightColor, lightDir);

    for (int y = 0; y < Config::YDIM; y++)
    {
        for (int x = 0; x < Config::XDIM; x++)
        {
            // map pixel to camera-space position
            float xpos = (x - Config::XDIM / 2) * 4.0f / Config::XDIM;
            float ypos = (y - Config::YDIM / 2) * 4.0f / Config::YDIM;

            Point3D screenPt;
            screenPt.set(xpos, ypos, 0);

            Ray3D ray;
            ray.set(camera, screenPt);

            Point3D  hitPoint;
            Vector3D hitNormal;
            ColorRGB pixelColor;
            pixelColor.set(30, 30, 80);   // sky blue background

            float    tMin = 1e9f;
            bool     hit  = false;

            // test stationary sphere
            Point3D p; Vector3D n;
            if (stationarySphere.get_intersection(ray, p, n))
            {
                float t = camera.distance(p);
                if (t < tMin) {
                    tMin = t; hit = true; hitPoint = p; hitNormal = n;
                    shader.SetObject(stationarySphere.color, 0.2, 0.5, 0.4, 20);
                    shader.GetShade(p, n, pixelColor);
                }
            }

            // test moving sphere
            if (movingSphere.get_intersection(ray, p, n))
            {
                float t = camera.distance(p);
                if (t < tMin) {
                    tMin = t; hit = true; hitPoint = p; hitNormal = n;
                    shader.SetObject(movingSphere.color, 0.2, 0.6, 0.3, 15);
                    shader.GetShade(p, n, pixelColor);
                }
            }

            // test floor plane
            if (floorPlane.get_intersection(ray, p, n))
            {
                float t = camera.distance(p);
                if (t < tMin) {
                    tMin = t; hit = true;
                    ColorRGB floorColor = floorPlane.get_checker_color(p);
                    shader.SetObject(floorColor, 0.3, 0.6, 0.1, 5);
                    shader.GetShade(p, n, pixelColor);
                }
            }

            (void)hit;   // suppress unused warning

            image[y][x][0] = (unsigned char)pixelColor.R;
            image[y][x][1] = (unsigned char)pixelColor.G;
            image[y][x][2] = (unsigned char)pixelColor.B;
        }
    }
}
```

---

### Step 1.5 — Call `step()` from `App::idle()`
**File:** `app/app.cpp`

In `App::idle()`, add a call to `rayTracer.step(dt)` before `rayTracer.traceScene()`:

```cpp
rayTracer.step(dt);
rayTracer.traceScene();
```

This is a one-line addition to what was already wired in Step 0.4.

**Checkpoint after Feature 1:** Window shows a yellow ball orbiting a grey sphere over a red/yellow checkerboard. The image animates every frame.

---

## Feature 2 – New Geometric Object (Cylinder)

**Goal:** Add a `Cylinder3D` class with ray intersection and render 2+ cylinders in the scene.

### Step 2.1 — Add `Cylinder3D` to ray classes
**File:** `core/ray_classes.h` and `core/ray_classes.cpp`

Add `Cylinder3D` after `Plane3D`:

```cpp
class Cylinder3D
{
 public:
   Point3D  center;
   float    radius;
   float    halfHeight;   // extends center.py ± halfHeight
   ColorRGB color;
   float    Ks;

   void set(Point3D c, float r, float hh, ColorRGB col, float ks = 0.0f);
   bool get_intersection(Ray3D ray, Point3D &hitPoint, Vector3D &hitNormal);
};
```

In `ray_classes.cpp`, implement `get_intersection`:
- Translate ray so cylinder axis is at x=0, z=0 (subtract center from ray origin).
- Solve the infinite cylinder: `(dx² + dz²)t² + 2(ox*dx + oz*dz)t + (ox² + oz² - r²) = 0`.
- Use quadratic formula (`B² - 4AC`); take smallest positive root.
- For that t, check `|hitY - center.py| <= halfHeight`; reject if outside.
- Also test top/bottom caps (flat discs at `center.py ± halfHeight`).
- Normal on curved surface: `(hit.px - center.px, 0, hit.pz - center.pz)` normalized.
- Normal on caps: `(0, ±1, 0)`.

---

### Step 2.2 — Add cylinders to `RayTracer`
**File:** `model/raytracer.h` and `model/raytracer.cpp`

Add to `raytracer.h`:
```cpp
#include <vector>
std::vector<Cylinder3D> cylinders;
```

In the constructor, push 2–3 cylinders at different positions, e.g.:
```cpp
Point3D c1; c1.set(-4, 0, 6);
ColorRGB blue; blue.set(50, 80, 200);
Cylinder3D cyl1; cyl1.set(c1, 0.6f, 2.0f, blue);
cylinders.push_back(cyl1);

Point3D c2; c2.set(4, 0, 6);
ColorRGB green; green.set(50, 180, 80);
Cylinder3D cyl2; cyl2.set(c2, 0.6f, 2.0f, green);
cylinders.push_back(cyl2);
```

---

### Step 2.3 — Include cylinders in `traceScene()` hit testing
**File:** `model/raytracer.cpp`

Add a cylinder loop inside the pixel loop, identical in structure to the sphere tests:

```cpp
for (auto& cyl : cylinders)
{
    if (cyl.get_intersection(ray, p, n))
    {
        float t = camera.distance(p);
        if (t < tMin) {
            tMin = t;
            shader.SetObject(cyl.color, 0.2, 0.5, 0.4, 20);
            shader.GetShade(p, n, pixelColor);
        }
    }
}
```

**Checkpoint after Feature 2:** Two coloured cylinders appear in the scene alongside the animated spheres and checkerboard floor.

---

## Feature 3 – Reflection Rays (Mirrors)

**Goal:** Cast a secondary reflection ray from each hit surface and blend it into the Phong color using a `Ks` coefficient.

### Step 3.1 — Add `Ks` field to `Cylinder3D`
**File:** `core/ray_classes.h`

Already added in Step 2.1 above. Set the stationary sphere's Ks to `0.5f` in the `RayTracer` constructor to make it clearly reflective for testing.

---

### Step 3.2 — Refactor `traceScene()` into a `castRay()` helper
**File:** `model/raytracer.h` and `model/raytracer.cpp`

Declare in `raytracer.h`:
```cpp
ColorRGB castRay(Ray3D ray, int depth);
```

Move all the per-pixel intersection + Phong shading logic from `traceScene()` into `castRay(ray, depth)`. `traceScene()` becomes:

```cpp
void RayTracer::traceScene()
{
    Point3D camera;
    camera.set(0, 0, -position);

    for (int y = 0; y < Config::YDIM; y++)
    {
        for (int x = 0; x < Config::XDIM; x++)
        {
            float xpos = (x - Config::XDIM / 2) * 4.0f / Config::XDIM;
            float ypos = (y - Config::YDIM / 2) * 4.0f / Config::YDIM;
            Point3D screenPt; screenPt.set(xpos, ypos, 0);
            Ray3D ray; ray.set(camera, screenPt);

            ColorRGB color = castRay(ray, 2);
            image[y][x][0] = (unsigned char)color.R;
            image[y][x][1] = (unsigned char)color.G;
            image[y][x][2] = (unsigned char)color.B;
        }
    }
}
```

`castRay` contains all the intersection logic and returns the final color. The `depth` parameter controls recursion; when `depth == 0`, skip reflection.

---

### Step 3.3 — Implement reflection inside `castRay()`
**File:** `model/raytracer.cpp`

At the end of `castRay`, after computing `pixelColor` from Phong, add:

```cpp
if (depth > 0 && hitKs > 0.0f)
{
    // R = D - 2*(D dot N)*N
    Vector3D D = ray.dir;
    float dDotN = D.dot(hitNormal);
    Vector3D N2 = hitNormal;
    N2.mult(2.0f * dDotN);
    D.sub(N2);
    D.normalize();

    // Offset origin to avoid self-intersection
    Point3D reflOrigin;
    Vector3D offset = hitNormal; offset.mult(0.001f);
    reflOrigin.set(hitPoint.px + offset.vx,
                   hitPoint.py + offset.vy,
                   hitPoint.pz + offset.vz);

    Ray3D reflRay; reflRay.set(reflOrigin, D);
    ColorRGB reflColor = castRay(reflRay, depth - 1);
    reflColor.mult(hitKs);
    pixelColor.add(reflColor);
}
return pixelColor;
```

`hitKs` is a local `float` set to the closest-hit object's `Ks` value during intersection testing.

---

### Step 3.4 — Tune Ks values and test
**File:** `model/raytracer.cpp`

Set Ks values in the constructor:
- `stationarySphere.Ks = 0.5f` — visible mirror reflections
- `movingSphere.Ks = 0.0f` — matte yellow (no reflection)
- Cylinder Ks around `0.2f` — subtle sheen

Run and adjust until the reflections look realistic without washing out the base color.

**Checkpoint after Feature 3:** The stationary sphere shows a reflected image of the checkerboard and the yellow moving sphere.

---

## Implementation Order

| # | Task | Files | Notes |
|---|------|-------|-------|
| 0.1 | Fix `render.h` | `view/render.h` | Remove broken reference; add `drawRayTracedImage` decl |
| 0.2 | Fix `render.cpp` | `view/render.cpp` | Remove bad ctor; implement `drawRayTracedImage` |
| 0.3 | Add `RayTracer` to `App` | `app/app.h` | Add member + include |
| 0.4 | Wire display/idle | `app/app.cpp` | Blit image in `display()`, call `traceScene` in `idle()` |
| 0.5 | Fix Makefile | `Makefile` | Add `core/ray_classes.o` + `model/raytracer.o` |
| 1.1 | Add `Plane3D` | `core/ray_classes.h/cpp` | Needed for floor |
| 1.2 | Add color/Ks to `Sphere3D` | `core/ray_classes.h` | Needed for colored spheres |
| 1.3 | Animation state in `RayTracer` | `model/raytracer.h/cpp` | Two spheres + orbit |
| 1.4 | Rewrite `traceScene()` | `model/raytracer.cpp` | Full Whitted scene |
| 1.5 | Call `step()` in `idle()` | `app/app.cpp` | Animate the moving sphere |
| 2.1 | Add `Cylinder3D` | `core/ray_classes.h/cpp` | New primitive with intersection |
| 2.2 | Add cylinders to scene | `model/raytracer.h/cpp` | Init 2+ cylinders |
| 2.3 | Cylinders in hit test | `model/raytracer.cpp` | Loop over `cylinders` vector |
| 3.1 | Ks on all objects | `core/ray_classes.h` | Done in 1.2 + 2.1 |
| 3.2 | Refactor to `castRay()` | `model/raytracer.h/cpp` | Prereq for recursion |
| 3.3 | Reflection logic | `model/raytracer.cpp` | R = D - 2(D·N)N |
| 3.4 | Tune Ks values | `model/raytracer.cpp` | Visual polish |

---

## Files Changed — Complete Summary

| File | Step | Type of Change |
|------|------|---------------|
| `view/render.h` | 0.1 | Remove `RayTracer& tracer`; add `drawRayTracedImage()` decl |
| `view/render.cpp` | 0.2 | Remove bad ctor; implement `drawRayTracedImage()` |
| `app/app.h` | 0.3 | Add `RayTracer` member and include |
| `app/app.cpp` | 0.4, 1.5 | Blit image in `display()`; call `step()` + `traceScene()` in `idle()` |
| `Makefile` | 0.5 | Add 2 object files to OBJS |
| `core/ray_classes.h` | 1.1, 1.2, 2.1 | Add `Plane3D`, `Cylinder3D`; add `color`/`Ks` to `Sphere3D` |
| `core/ray_classes.cpp` | 1.1, 2.1 | Implement `Plane3D` and `Cylinder3D` methods |
| `model/raytracer.h` | 1.3, 2.2, 3.2 | Add scene members, `step()`, `cylinders`, `castRay()` |
| `model/raytracer.cpp` | 1.4, 2.3, 3.2, 3.3, 3.4 | Rewrite `traceScene()`, add `step()`, `castRay()`, reflection |

> No new files are created. All changes extend existing files.
