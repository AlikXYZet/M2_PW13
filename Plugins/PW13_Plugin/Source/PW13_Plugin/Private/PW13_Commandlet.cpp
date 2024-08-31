
// Base:
#include "PW13_Commandlet.h"

// Interaction:
#include "PW13_Tools.h"

// UE:
#include "Engine/StaticMesh.h"
#include "AssetRegistryModule.h"
//--------------------------------------------------------------------------------------



int32 UGenerateLODsCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	//TMap<FString, FString> ParamsMap;

	ParseCommandLine(*Params, Tokens, Switches);
	// -run=GenerateLODs -GenerateLod /Game/StarterContent/Props /Game/StarterContent/Shapes

	if (Tokens.Num() > 0)
	{
		if (Switches.Contains(TEXT("GenerateLod")))
		{
			ProcessAssets(Tokens);
		}
	}

	return 0;
}

void UGenerateLODsCommandlet::ProcessAssets(TArray<FString>& RootDirectories)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
		AssetRegistryConstants::ModuleName);

	AssetRegistryModule.Get().SearchAllAssets(true);

	FString ClassName = TEXT("StaticMesh");
	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssetsByClass(*ClassName, AssetList, true);

	TArray<UObject*> MutableObjects;

	for (FAssetData AssetData : AssetList)
	{
		for (FString RootDirectory : RootDirectories)
		{
			if (AssetData.ObjectPath.ToString().StartsWith(RootDirectory, ESearchCase::IgnoreCase))
			{
				UObject* AssetInstance = AssetData.GetAsset();

				MutableObjects.Add(AssetInstance);

				break;
			}
		}
	}

	if (MutableObjects.Num() > 0)
	{
		TArray<FEditorScriptingMeshReductionSettings> ReductionSettings;
		FEditorScriptingMeshReductionSettings Settings;

		//LOD 0
		Settings.PercentTriangles = 1;
		Settings.ScreenSize = 0.9;
		ReductionSettings.Add(Settings);

		//LOD 1
		Settings.PercentTriangles = 0.5;
		Settings.ScreenSize = 0.5;
		ReductionSettings.Add(Settings);

		//LOD 2
		Settings.PercentTriangles = 0.1;
		Settings.ScreenSize = 0.3;
		ReductionSettings.Add(Settings);

		FEditorScriptingMeshReductionOptions Options;
		Options.ReductionSettings = ReductionSettings;

		UPW13_Tools::SetLODsForStaticMeshes(MutableObjects, ReductionSettings);
	}
}
