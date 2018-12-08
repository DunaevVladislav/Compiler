SET VS_path="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community"
SET cur_vers=\VC\Tools\MSVC\14.15.26726
SET cl_path=%cur_vers%\bin\Hostx86\x86\cl.exe
SET C_VS_PATH=%VS_path%%cur_vers%
SET Windows_kit_path="C:\Program Files (x86)\Windows Kits\10"
bool-lang.exe source_example.blng
%VS_path%%cl_path% /EHsc /I %C_VS_PATH%\include /I %Windows_kit_path%\Include\10.0.16299.0\ucrt source_example.cpp /link /LIBPATH:%C_VS_PATH%\lib\x86 /LIBPATH:%Windows_kit_path%\Lib\10.0.17134.0\um\x86 /LIBPATH:%Windows_kit_path%\Lib\10.0.17134.0\ucrt\x86