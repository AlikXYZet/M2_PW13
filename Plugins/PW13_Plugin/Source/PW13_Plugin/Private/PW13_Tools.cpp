
// Base:
#include "PW13_Tools.h"
//--------------------------------------------------------------------------------------



void UPW13_Tools::SetLODsForStaticMeshes(TArray<UObject*> Objects, TArray<FEditorScriptingMeshReductionSettings> InputLODs)
{
	// Проверка на наличие настроек LOD
	if (InputLODs.Num() > 0)
	{
		// Массив для хранения UStaticMesh* после фильтрации
		TArray<UStaticMesh*> lStaticMeshes;

		// Фильтрация "Objects" до валидных UStaticMesh*
		if (CastToStaticMesh(Objects, lStaticMeshes))
		{
			FEditorScriptingMeshReductionOptions Options;
			Options.ReductionSettings = InputLODs;

			for (UStaticMesh* Data : lStaticMeshes)
			{
				UEditorStaticMeshLibrary::SetLods(Data, Options);

				Data->MarkPackageDirty();

				SaveAsset(Data);
			}
		}
		else
		{
			// LOG: Ни один из Ассетов не является UStaticMesh
			UE_LOG(LogClass, Warning, TEXT("None of the Assets is UStaticMesh!"));
		}
	}
	else
	{
		// LOG: Нет настроек LOD
		UE_LOG(LogClass, Warning, TEXT("No LOD settings!"));
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

bool UPW13_Tools::CastToStaticMesh(const TArray<UObject*>& iObjects, TArray<UStaticMesh*>& oStaticMeshes)
{
	// Отфильтрованный элемент массива
	UStaticMesh* lDataStaticMesh = nullptr;

	// Фильтрация
	for (UObject* Data : iObjects)
	{
		lDataStaticMesh = Cast<UStaticMesh>(Data);

		if (lDataStaticMesh)
		{
			oStaticMeshes.Add(lDataStaticMesh);
		}
	}

	// Результат фильтрации
	if (oStaticMeshes.Num() > 0)
		return true;
	else
		return false;
}
