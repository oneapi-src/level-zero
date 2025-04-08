# escape=`

ARG BASE_IMAGE=mcr.microsoft.com/dotnet/framework/runtime:4.8
FROM ${BASE_IMAGE}

SHELL ["powershell"]
ENV VS_VERSION=2022
RUN [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
    Switch ($env:VS_VERSION) { `
        "2019" {$url_version = "16"} `
        "2022" {$url_version = "17"} `
        default {echo "Unsupported VS version $env:VS_VERSION"; EXIT 1} `
    }; `
    wget -Uri https://aka.ms/vs/${url_version}/release/vs_buildtools.exe -OutFile vs_buildtools.exe
SHELL ["cmd", "/S", "/C"]
RUN (start /w vs_buildtools.exe --quiet --wait --norestart --nocache `
        --installPath "%ProgramFiles(x86)%\Microsoft Visual Studio\%VS_VERSION%\BuildTools" `
        --add Microsoft.Component.MSBuild `
        --add Microsoft.VisualStudio.Component.VC.CoreBuildTools `
        --add Microsoft.VisualStudio.Component.VC.Redist.14.Latest `
        --add Microsoft.VisualStudio.Component.Windows10SDK `
        --add Microsoft.VisualStudio.ComponentGroup.NativeDesktop.Core `
        --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        --add Microsoft.VisualStudio.Component.Windows10SDK.19041 `
        --add Microsoft.VisualStudio.Component.VC.Runtimes.x86.x64.Spectre `
        || IF "%ERRORLEVEL%"=="3010" EXIT 0) `
    && del /q vs_buildtools.exe `
    && mklink /d "C:\Program Files (x86)\Microsoft Visual Studio\current" "C:\Program Files (x86)\Microsoft Visual Studio\%VS_VERSION%" `
    && if not exist "C:\Program Files (x86)\Microsoft Visual Studio\%VS_VERSION%\BuildTools\Common7\Tools\VsDevCmd.bat" exit 1
ENTRYPOINT ["C:\\Program Files (x86)\\Microsoft Visual Studio\\current\\BuildTools\\VC\\Auxiliary\\Build\\vcvars64.bat", "&&"]

SHELL ["powershell"]
ENV chocolateyUseWindowsCompression false
RUN Set-ExecutionPolicy Bypass -Scope Process -Force; `
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
SHELL ["cmd", "/S", "/C"]
RUN call "%ProgramFiles(x86)%\Microsoft Visual Studio\current\BuildTools\VC\Auxiliary\Build\vcvars64.bat" && `
    powershell -command "[Environment]::SetEnvironmentVariable('Path', $env:Path, [System.EnvironmentVariableTarget]::Machine)"
RUN choco feature disable --name showDownloadProgress && `
    choco install -y --fail-on-error-output git -params '"/GitAndUnixToolsOnPath"' && `
    choco install -y --fail-on-error-output 7zip && `
    choco install -y --fail-on-error-output ccache && `
    choco install -y --fail-on-error-output cmake.install --installargs 'ADD_CMAKE_TO_PATH=System' && `
    choco install -y --fail-on-error-output ninja
