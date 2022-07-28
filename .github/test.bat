cd ..
for /f %%i in ('where /r test *.xml') do set variable=%%i
type %variable%