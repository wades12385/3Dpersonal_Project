// 명령어		옵션			복사할 디렉터리				붙여넣을 디렉터리
xcopy			/y			.\Engine\Codes\*.h		.\Reference\Headers\
xcopy			/y			.\Engine\Codes\*.inl		.\Reference\Headers\
xcopy			/y			.\Engine\Codes\*.hlsl		.\Reference\Headers\
xcopy			/y			.\Engine\Codes\*.hpp		.\Reference\Headers\

xcopy			/y			.\Engine\Bin\*.lib			.\Reference\Libraries\
xcopy			/y			.\Engine\Bin\*.dll			.\Client\Bin\
xcopy			/y			.\Engine\Bin\*.dll			.\MFCApplication1\