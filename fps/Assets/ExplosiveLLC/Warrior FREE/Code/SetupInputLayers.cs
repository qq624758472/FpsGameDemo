using UnityEditor;
using UnityEngine;

namespace WarriorAnimsFREE
{
	class SetupInputLayers:AssetPostprocessor
	{
		static void OnPostprocessAllAssets(string[] importedAssets, string[] deletedAssets, string[] movedAssets, string[] movedFromAssetPaths)
		{
			SetupMessageWindow window = ( SetupMessageWindow )EditorWindow.GetWindow(typeof(SetupMessageWindow), true, "Load Input and Tag Presets");
			window.maxSize = new Vector2(310f, 115f);
			window.minSize = window.maxSize;
		}
	}

	public class SetupMessageWindow:EditorWindow
	{
		void OnGUI()
		{
			EditorGUILayout.LabelField("Before attempting to use the Warrior Animation Mecaim Animation Packs, you must first ensure that the layers and inputs are correctly defined.  There is an included Input.preset and Layer.preset which contains all the settings that you can load in.\n \nYou can remove this message by deleting the SetupInputLayers.cs script.", EditorStyles.wordWrappedLabel);
		}
	}
}