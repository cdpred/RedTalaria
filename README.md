# RedTalaria URLs for Unreal Engine

RedTalaria is a plugin for Unreal Engine that builds on [Hermes](https://github.com/jorgenpt/Hermes) and provides a collection of Hermes endpoints to link "parts" of your project and share them with your team e.g. through Slack.

Big thanks to [Jørgen P. Tjernø](https://github.com/jorgenpt) for [Hermes](https://github.com/jorgenpt/Hermes)!

# Engine compatibilty

RedTalaria was tested (and thus should be compatible) with UE 5.3 and UE 4.27.

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

## Linking BehaviorTree nodes
This feature is only available in UE 5.3+, if you are using a source build, make sure you have [this commit](https://github.com/EpicGames/UnrealEngine/commit/6bb52ead8294554e5bdb60f637729eae397942d8).

Once you've set up RedTalaria, you should be able to right click on any BehaviorTree node and see a new `Copy 'Focus node' URL` option:

[<img src="README_link_behavior_tree_node_focus.png?raw=true">](README_link_behavior_tree_node_focus.png?raw=true)

Clicking on links like these will open up the asset in the editor and focus on the linked node.

## Linking Levels at a specific camera position
Once you've set up RedTalaria, under the Viewport options menu you should see a new `Copy camera coords URL` option (it will only be active for perspective viewports):

[<img src="README_link_level_at_camera_coords.png?raw=true">](README_link_level_at_camera_coords.png?raw=true)

Clicking on links like these will open up the level at the exact camera location / rotation for when the link was made.

## Linking folders in the content browser

Once you've set up RedTalaria, when right clicking on a folder in the content browser you should see a new `Copy folder URL` option:

[<img src="README_link_content_folder_1.png?raw=true">](README_link_content_folder_1.png?raw=true)
[<img src="README_link_content_folder_2.png?raw=true">](README_link_content_folder_2.png?raw=true)

Clicking on links like these will focus the given folder in the content browser.

## Linking level actors
This feature is only available in UE 5.3+, and only for actors with external packaging ([OFPA](https://docs.unrealengine.com/5.3/en-US/one-file-per-actor-in-unreal-engine/)).

Once you've set up RedTalaria, you should be able to right click on any actor placed in a level or in the outliner and see a new `Copy selected actor URL(s)` option:

[<img src="README_link_level_actor_from_viewport.png?raw=true">](README_link_level_actor_from_viewport.png?raw=true)
[<img src="README_link_level_actor_from_outliner.png?raw=true">](README_link_level_actor_from_outliner.png?raw=true)

Clicking on links like these will open up the level the actor is placed in, select the actor in the outliner and focus the camera on the actor.
If the level is partitioned, the actor will be loaded (even if it resides in a currently unloaded region).

## Linking automated tests
This feature is only available in UE 5+.

Once you've set up RedTalaria, you should be able to link automated tests like so:
```
YOUR_PROJECT://automation?test_name_filter=YOUR_TEST_NAME_FILTER_STRING_URL_ENCODED
```
Spaces in the test name filter have to be encoded as `%20`.

Clicking on links like these will open up the session frontend window and execute all tests matching the given test name filter.

Example links to engine provided tests (for UE 5.3 projects):
* `YOUR_PROJECT://automation?test_name_filter=TestFramework.Log.Add%20Log%20Message` (runs one test)
* `YOUR_PROJECT://automation?test_name_filter=TestFramework.Log` (runs 3 tests)

# Extending

## Creating custom URLs for graph nodes
Take a look at [RedHermesGraphNodeEndpoint](Source/RedHermesGraphNodeEndpoint/Public/RedHermesGraphNodeEndpoint.h) & [RedHermesGraphNodeEndpointEditorExtension](Source/RedHermesGraphNodeEndpoint/Public/RedHermesGraphNodeEndpointEditorExtension.h), which serve as a base for linking graph nodes, and
[RedHermesBlueprintNodeEndpoint](Source/RedHermesBlueprintNodeEndpoint/Public/RedHermesBlueprintNodeEndpoint.h) as a concrete example building on them.

## Creating custom URLs with your own functionality
Take a look at [RedHermesEndpoint](Source/RedTalaria/Public/RedHermesEndpoint.h), which serves as a base for custom Hermes endpoints, and [RedHermesLevelAtCameraCoordsEndpoint](Source/RedHermesLevelAtCameraCoordsEndpoint/Public/RedHermesLevelAtCameraCoordsEndpoint.h) & [RedHermesLevelAtCameraCoordsEndpointEditorExtension](Source/RedHermesLevelAtCameraCoordsEndpoint/Public/RedHermesLevelAtCameraCoordsEndpointEditorExtension.h) as a concrete example building on it.

# License

Hermes icons ([Icon128.png](Resources/Icon128.png) & [RedTalaria_16.png](Content/Editor/Slate/RedTalaria_16.png)) created by max.icons - [Flaticon](https://www.flaticon.com/free-icons/hermes).

RedTalaria is licensed under the MIT license ([LICENSE](LICENSE.txt) or http://opensource.org/licenses/MIT).
