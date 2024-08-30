#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "PW13_Tools.generated.h"


UCLASS(BlueprintType, Blueprintable)
class PW13_PLUGIN_API UPW13_Tools : public UObject
{
	GENERATED_BODY()
public:

	//FPW13_Tools();
	//~FPW13_Tools();

	UFUNCTION(BlueprintCallable, Category = "PW13_Tools")
	void SetLodsForStaticMeshes(TArray<UStaticMesh*> StaticMeshes);

private:

	void SaveAsset(UObject* AssetInstance);
};
