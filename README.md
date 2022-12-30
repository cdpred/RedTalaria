# RedTalaria URLs for Unreal Engine

RedTalaria is a plugin for Unreal Engine that builds on [Hermes](https://github.com/jorgenpt/Hermes) and provides a collection of Hermes endpoints to link "parts" of your project and share them with your team e.g. through Slack.

Big thanks to [Jørgen P. Tjernø](https://github.com/jorgenpt) for [Hermes](https://github.com/jorgenpt/Hermes)!

# Engine compatibilty

RedTalaria was tested (and thus should be compatible) with UE 5.1 and UE 4.27.

# Setup

1. Setup [Hermes](https://github.com/jorgenpt/Hermes#setup).
2. Clone this repository into your project's Plugins folder.
3. Start your editor and enjoy your new Hermes endpoints.

# Using

## Linking Blueprint nodes
Once you've set up RedTalaria, you should be able to right click on any Blueprint node and see a new `Copy 'Focus node' URL` option:

[<img src="README_link_blueprint_node_focus.png?raw=true">](README_link_blueprint_node_focus.png?raw=true)

Clicking on links like these will open up the asset in the editor and focus on the linked node.

---

For nodes that have a jump target, you'll see an additional `Copy 'Open node' URL` option:

[<img src="README_link_blueprint_node_jump_target.png?raw=true">](README_link_blueprint_node_jump_target.png?raw=true)

Clicking on links like these will open up the (jump target of the) linked node in the editor.

## Linking Levels at a specific camera position
Once you've set up RedTalaria, under the Viewport options menu you should see a new `Copy camera coords URL` option (it will only be active for perspective viewports):

[<img src="README_link_level_at_camera_coords.png?raw=true">](README_link_level_at_camera_coords.png?raw=true)

Clicking on links like these will open up the level at the exact camera location / rotation for when the link was made.

# Extending

## Creating custom URLs for graph nodes
Take a look at [RedHermesGraphNodeEndpoint](Source/RedHermesGraphNodeEndpoint/Public/RedHermesGraphNodeEndpoint.h) & [RedHermesGraphNodeEndpointEditorExtension](Source/RedHermesGraphNodeEndpoint/Public/RedHermesGraphNodeEndpointEditorExtension.h), which serve as a base for linking graph nodes, and
[RedHermesBlueprintNodeEndpoint](Source/RedHermesBlueprintNodeEndpoint/Public/RedHermesBlueprintNodeEndpoint.h) as a concrete example building on them.

## Creating custom URLs with your own functionality
Take a look at [RedHermesEndpoint](Source/RedTalaria/Public/RedHermesEndpoint.h), which serves as a base for custom Hermes endpoints, and [RedHermesLevelAtCameraCoordsEndpoint](Source/RedHermesLevelAtCameraCoordsEndpoint/Public/RedHermesLevelAtCameraCoordsEndpoint.h) & [RedHermesLevelAtCameraCoordsEndpointEditorExtension](Source/RedHermesLevelAtCameraCoordsEndpoint/Public/RedHermesLevelAtCameraCoordsEndpointEditorExtension.h) as a concrete example building on it.

# License

Hermes icons ([Icon128.png](Resources/Icon128.png) & [RedTalaria_16.png](Content/Editor/Slate/RedTalaria_16.png)) created by max.icons - [Flaticon](https://www.flaticon.com/free-icons/hermes).

RedTalaria is licensed under the MIT license ([LICENSE](LICENSE.txt) or http://opensource.org/licenses/MIT).
