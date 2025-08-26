// Copyright Phyronnaz

#pragma once

#include "CoreMinimal.h"

class UHLSLMaterialFunctionLibrary;

class FHLSLMaterialMessages
{
public:
	// template <typename FmtType, typename... Types>
	// static void ShowError(const FmtType& Fmt, Types... Args)
	// {
	// 	ShowErrorImpl(FString::Printf(Fmt, Args...));
	// }
	
	static void ShowError(const TCHAR* Fmt, ...)
	{
		TCHAR TempMsg[1024];
		va_list Args;
    
		va_start(Args, Fmt);
		FCString::GetVarArgs(TempMsg, UE_ARRAY_COUNT(TempMsg), Fmt, Args);
		va_end(Args);
    
		ShowErrorImpl(TempMsg);
	}

	static void ShowError(const FString& Message)
	{
		ShowErrorImpl(Message);
	}
	
	class FLibraryScope
	{
	public:
		explicit FLibraryScope(UHLSLMaterialFunctionLibrary& InLibrary)
			: Guard(Library, &InLibrary)
		{
		}

	private:
		static UHLSLMaterialFunctionLibrary* Library;
		TGuardValue<UHLSLMaterialFunctionLibrary*> Guard;

		friend class FHLSLMaterialMessages;
	};

private:
	static void ShowErrorImpl(FString Message);
};