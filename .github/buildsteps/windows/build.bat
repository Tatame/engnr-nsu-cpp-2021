cd "%LAB_INDEX%"                                              || exit /b 1

cd build                                                      || exit /b 1

cmake --version                                               || exit /b 1

@echo.
@echo.

@echo ============================= BUILD x86_64 ==============================
cmake -E rm -rf "x86_64"                                      || exit /b 1
cmake -G "Visual Studio 16 2019" -A x64 -B "x86_64" -S ".."   || exit /b 1
@echo.
@echo.                             x86_64 (Debug)
cmake --build "x86_64" --config Debug                         || exit /b 1
@echo.
@echo.                            x86_64 (Release)
cmake --build "x86_64" --config Release                       || exit /b 1

@echo.
@echo x86_64 configurations (Debug and Release) have been built successfully.
@echo =========================================================================

@echo.
@echo.

@echo Passed.
