# Plan: Website Deployment and Mobile Compatibility

## Phase 1: PWA and Mobile Assets
- [x] Task: Generate PWA Assets [9125707]
    - [x] Create a `manifest.json` file in `src/web/`.
    - [x] Create a stylized Geometric icon (PNG/SVG) for the PWA.
- [x] Task: Service Worker Implementation [9125707]
    - [x] Write a basic Service Worker for offline asset caching.
    - [x] Register the Service Worker in `index.html`.
- [ ] Task: Conductor - User Manual Verification 'PWA and Mobile Assets' (Protocol in workflow.md)

## Phase 2: Mobile UX and Compatibility
- [x] Task: Responsive Design Refinement [9125707]
    - [x] Audit touch targets and ensure minimum 44x44px.
    - [x] Add meta viewport tags and prevent zooming.
- [x] Task: iOS Platform Modal [9125707]
    - [x] Implement an auto-detect modal for iOS browsers.
    - [x] Provide instructions for Bluefy/WebBLE apps.
- [x] Task: HTTPS Context Guard [9125707]
    - [x] Add a check for `window.isSecureContext` and alert users if not on HTTPS.
- [ ] Task: Conductor - User Manual Verification 'Mobile UX and Compatibility' (Protocol in workflow.md)

## Phase 3: Netlify Deployment
- [x] Task: Hosting Configuration [54e9daf]
    - [x] Create a `netlify.toml` file to configure the build and headers.
    - [x] Ensure HTTPS and caching headers are set correctly.
- [x] Task: Final Deployment [54e9daf]
    - [x] Deploy the `src/web/` directory to Netlify (Via Git).
    - [x] Verify the live URL on Android and iOS.
- [x] Task: Conductor - User Manual Verification 'Netlify Deployment' (Protocol in workflow.md) [54e9daf]
