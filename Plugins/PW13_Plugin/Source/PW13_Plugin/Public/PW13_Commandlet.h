#pragma once

// Base:
#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"

// Generated:
#include "PW13_Commandlet.generated.h"
//--------------------------------------------------------------------------------------



UCLASS()
class PW13_PLUGIN_API UGenerateLODsCommandlet : public UCommandlet
{
	GENERATED_BODY()

	virtual int32 Main(const FString& Params) override;

	void ProcessAssets(TArray<FString>& RootDirectories);
};
