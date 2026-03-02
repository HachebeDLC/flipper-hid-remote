# Plan: Website Deployment and Mobile Compatibility

## Phase 1: PWA and Mobile Assets
- [ ] Task: Generate PWA Assets
    - [ ] Create a `manifest.json` file in `src/web/`.
    - [ ] Create a stylized Geometric icon (PNG/SVG) for the PWA.
- [ ] Task: Service Worker Implementation
    - [ ] Write a basic Service Worker for offline asset caching.
    - [ ] Register the Service Worker in `index.html`.
- [ ] Task: Conductor - User Manual Verification 'PWA and Mobile Assets' (Protocol in workflow.md)

## Phase 2: Mobile UX and Compatibility
- [ ] Task: Responsive Design Refinement
    - [ ] Audit touch targets and ensure minimum 44x44px.
    - [ ] Add meta viewport tags and prevent zooming.
- [ ] Task: iOS Platform Modal
    - [ ] Implement an auto-detect modal for iOS browsers.
    - [ ] Provide instructions for Bluefy/WebBLE apps.
- [ ] Task: HTTPS Context Guard
    - [ ] Add a check for `window.isSecureContext` and alert users if not on HTTPS.
- [ ] Task: Conductor - User Manual Verification 'Mobile UX and Compatibility' (Protocol in workflow.md)

## Phase 3: Netlify Deployment
- [ ] Task: Hosting Configuration
    - [ ] Create a `netlify.toml` file to configure the build and headers.
    - [ ] Ensure HTTPS and caching headers are set correctly.
- [ ] Task: Final Deployment
    - [ ] Deploy the `src/web/` directory to Netlify.
    - [ ] Verify the live URL on Android and iOS.
- [ ] Task: Conductor - User Manual Verification 'Netlify Deployment' (Protocol in workflow.md)
