<#
 Copyright (C) 2025 Intel Corporation
 SPDX-License-Identifier: MIT
#>

param (
    [string]$sdkVersion,
    [string]$installPath,
    [string]$removeSdkEnvVar
)

if ($removeSdkEnvVar) {
    if ($removeSdkEnvVar -eq "1" -or $removeSdkEnvVar -eq "true") {
        Write-Output "true"
        $removeSdkEnvVarValue = $true
    } elseif ($removeSdkEnvVar -eq "0" -or $removeSdkEnvVar -eq "false") {
        $removeSdkEnvVarValue = $false
    } else {
        Write-Error "Invalid value for 'removeSdkEnvVar'. Must be a boolean value 0,1,true,false."
        Write-Output "Usage: .\level_zero_sdk_setup.ps1 -sdkVersion 1.21.1 -installPath C:\ -removeSdkEnvVar 1"
        exit 1
    }
} else {
    $removeSdkEnvVarValue = $false
}

if (-not $sdkVersion) {
    Write-Error "Parameter 'sdkVersion' is required. Example: 1.21.1"
    Write-Output "Usage: .\level_zero_sdk_setup.ps1 -sdkVersion 1.21.1 -installPath C:\ -[optional]removeSdkEnvVar 1"
    Write-Output "Usage: .\level_zero_sdk_setup.ps1 -sdkVersion 1.21.1 -installPath C:\"
    exit 1
}

if (-not $installPath) {
    Write-Error "Parameter 'installPath' is required.  Example: C:\Users\user\LevelZeroSDK, where LevelZeroSDK is the root directory. Default is SYSTEM_DRIVE:\"
    Write-Output "Usage: .\level_zero_sdk_setup.ps1 -sdkVersion 1.21.1 -installPath C:\Users\user\LevelZeroSDK -[optional]removeSdkEnvVar 1"
    Write-Output "Usage: .\level_zero_sdk_setup.ps1 -sdkVersion 1.21.1 -installPath C:\Users\user\LevelZeroSDK"
    exit 1
}

# Update or set the LEVEL_ZERO_SDK_V<major_version>_PATH environment variable
$majorVersion = $sdkVersion.Split('.')[0]
$envVarName = "LEVEL_ZERO_V${majorVersion}_SDK_PATH"

if ($removeSdkEnvVarValue -eq $true) {
    if (-not [System.Environment]::GetEnvironmentVariable($envVarName, [System.EnvironmentVariableTarget]::Machine)) {
        Write-Error "Environment variable does not exist: $envVarName"
        exit 1
    }
    [System.Environment]::SetEnvironmentVariable($envVarName, $null, [System.EnvironmentVariableTarget]::Machine)
    Write-Output "Environment variable removed: $envVarName"
} else {
    # Define the paths
    $sdkPath = Join-Path -Path $installPath -ChildPath "LevelZeroSDK\$sdkVersion\"

    # Check if the SDK path exists
    if (-not (Test-Path -Path $sdkPath)) {
        Write-Error "The Level Zero SDK path '$sdkPath' does not exist."
        exit 1
    }
    $currentEnvPath = [System.Environment]::GetEnvironmentVariable($envVarName, [System.EnvironmentVariableTarget]::Machine)
    if ($null -eq $currentEnvPath -or $currentEnvPath -notcontains $sdkPath) {
        [System.Environment]::SetEnvironmentVariable($envVarName, $sdkPath, [System.EnvironmentVariableTarget]::Machine)
    }
    Write-Output "Level Zero SDK Path Setup completed successfully."
    Write-Output "Environment variable changed: $envVarName"
    Write-Output "Updated SDK Version: $sdkVersion"
    Write-Output "Updated SDK Path: $sdkPath"
}