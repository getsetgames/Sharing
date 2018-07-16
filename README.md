iOS Sharing
===
A plugin for Unreal Engine 4 that enables native sharing on iOS

How to use:
---

# Create a blueprint with both "screenshot" and "sharing" components added to the component tree
# Take a screenshot using the default Unreal command: "Execute Console Command" node with the value "SHOT" or "highresshot 1"
# With the screenshot component selected in the details pane select "Screenshot Captured Image" to create an event that listens to when unreal has created a screenshot. Use the image output as in input for the "Share" BP node
