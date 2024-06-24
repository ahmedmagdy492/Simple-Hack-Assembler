@echo off

mkdir test_output

g++ .\src\Utils.cpp .\src\tests\CodeExtractorTests.cpp -o test_output/CodeExtractorTests.exe
g++ .\src\Utils.cpp .\src\tests\ContainsLettersOnlyTests.cpp -o test_output/ContainsLettersOnlyTests.exe
g++ .\src\Utils.cpp .\src\tests\IsStringAlphaNumericTests.cpp -o test_output/IsStringAlphaNumericTests.exe
g++ .\src\Utils.cpp .\src\tests\IsStringUpperCaseTests.cpp -o test_output/IsStringUpperCaseTests.exe
g++ .\src\Utils.cpp .\src\tests\LabelExtractorTests.cpp -o test_output/LabelExtractorTests.exe
g++ .\src\Utils.cpp .\src\tests\SplitStringTests.cpp -o test_output/SplitStringTests.exe
g++ .\src\Utils.cpp .\src\tests\TrimStringTests.cpp -o test_output/TrimStringTests.exe
g++ .\src\Utils.cpp .\src\tests\SymbolsResolverTests.cpp -o test_output/SymbolsResolverTests.exe
g++ .\src\Utils.cpp .\src\tests\TestTrimEnd.cpp -o test_output/TestTrimEnd.exe

echo:
echo running tests...
echo:
echo ==============================================================
echo:
test_output\CodeExtractorTests.exe
echo ==============================================================
echo:
test_output\ContainsLettersOnlyTests.exe
echo ==============================================================
echo:
test_output\IsStringAlphaNumericTests.exe
echo:
echo ==============================================================
test_output\IsStringUpperCaseTests.exe
echo:
echo ==============================================================
test_output\LabelExtractorTests.exe
echo:
echo ==============================================================
test_output\SplitStringTests.exe
echo:
echo ==============================================================
test_output\TrimStringTests.exe
echo:
echo ==============================================================
test_output\SymbolsResolverTests.exe
echo:
echo ==============================================================
test_output\TestTrimEnd.exe