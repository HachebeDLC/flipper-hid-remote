# Spec: Website Deployment and Mobile Compatibility

## Overview
This track focuses on making the Flipper HID Remote dashboard accessible globally via HTTPS (required for Web Bluetooth) using Netlify, while enhancing the mobile experience through PWA (Progressive Web App) features and cross-device compatibility testing.

## Functional Requirements
1. **Netlify Deployment:**
   - Configure the `src/web/` directory for static hosting on Netlify.
   - Implement a basic deployment workflow (Git Integration).

2. **PWA Integration:**
   - Implement a `manifest.json` to allow home screen installation.
   - Add a simple Service Worker for basic asset caching (offline shell).
   - Generate a Geometric/Stylized icon for the installation prompt.

3. **Mobile Compatibility & UX:**
   - Ensure the UI is responsive and usable on small touchscreens (44x44px minimum touch targets).
   - Implement an "Instructions" modal specifically for iOS users (explaining Bluefy/WebBLE requirements).

4. **HTTPS Enforcement:**
   - Ensure the app correctly handles non-secure contexts by informing the user that Web Bluetooth requires HTTPS.

## Non-Functional Requirements
- **Fast Load Times:** PWA caching should enable near-instant loading after the first visit.
- **Security:** Use Subresource Integrity (SRI) if any external libraries are added (though currently none are used).

## Acceptance Criteria
- Dashboard is accessible at a `.netlify.app` sub-domain.
- "Add to Home Screen" prompt works on Android and iOS (via supported browsers).
- Web Bluetooth connection is successful when accessed via HTTPS on a mobile device.
- UI remains functional and aesthetically consistent across different screen widths.
