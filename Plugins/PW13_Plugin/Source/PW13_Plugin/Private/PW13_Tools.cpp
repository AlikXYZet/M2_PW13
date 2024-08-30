#include "PW13_Tools.h"
#include "EditorStaticMeshLibrary.h"



void UPW13_Tools::SetLodsForStaticMeshes(TArray<UStaticMesh*> StaticMeshes)
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

	for (UStaticMesh*& Data : StaticMeshes)
	{
		if (Data)
		{
			UEditorStaticMeshLibrary::SetLods(Data, Options);

			Data->MarkPackageDirty();

			SaveAsset(Data);
		}
	}
}

void UPW13_Tools::SaveAsset(UObject* AssetInstance)
{
	if (AssetInstance)
	{
		if (UPackage* Package = AssetInstance->GetPackage())
		{
			if (Package->IsDirty())
			{
				FString PackageName = FPackageName::LongPackageNameToFilename(
					Package->GetPathName(), FPackageName::GetAssetPackageExtension());

				UE_LOG(LogClass, Log, TEXT("Saving asset to: %s..."), *PackageName);

				if (Package->SavePackage(Package, AssetInstance, RF_Standalone, *PackageName, GLog))
				{
					UE_LOG(LogClass, Log, TEXT("Done."));
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("Can't save asset!"));
				}
			}
		}
	}
}
