#pragma once

// Base:
#include "CoreMinimal.h"

// Plugins:
#include "EditorStaticMeshLibrary.h"

// Generated:
#include "PW13_Tools.generated.h"
//--------------------------------------------------------------------------------------



UCLASS()
class PW13_PLUGIN_API UPW13_Tools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** PS: Ключевое слово "static" ОБЯЗАТЕЛНО ! */

public:

	/** Метод по заданию: Генерирует LOD для UStaticMesh
	@param	Objects - Массив UObject для которых требуется генерация LOD (Будет отфильтрован до UStaticMesh)
	@param	InputLODs - Массив настроек LOD
	*/
	UFUNCTION(BlueprintCallable, Category = "PW13_Plugin|LOD")
	static void SetLODsForStaticMeshes(TArray<UObject*> Objects, TArray<FEditorScriptingMeshReductionSettings> InputLODs);

private:

	/** Сохранение Ассетов
	@param	AssetInstance - Экземпляр Ассета, который необходимо сохранить
	*/
	static void SaveAsset(UObject* AssetInstance);

	/**	Фильтрация всего лишнего, кроме UStaticMesh
	@param	Objects - Объекты фильтрации
	@param	oStaticMeshes - Массив для хранения UStaticMesh* после фильтрации
	@return	Результат фильтрации: true, если есть элемент класса UStaticMesh
	*/
	static bool CastToStaticMesh(const TArray<UObject*>& iObjects, TArray<UStaticMesh*>& oStaticMeshes);
};
