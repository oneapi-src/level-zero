"""
 Copyright (C) 2025 Intel Corporation
 SPDX-License-Identifier: MIT
"""

param (
    [string]$sdkVersion,
    [string]$installPath
)

# Define the paths
$sdkPath = Join-Path -Path $installPath -ChildPath "LevelZeroSDK\$sdkVersion\"

# Update or set the LEVEL_ZERO_SDK_V<major_version>_PATH environment variable
$majorVersion = $sdkVersion.Split('.')[0]
$envVarName = "LEVEL_ZERO_V${majorVersion}_SDK_PATH"
$currentEnvPath = [System.Environment]::GetEnvironmentVariable($envVarName, [System.EnvironmentVariableTarget]::Machine)
if ($null -eq $currentEnvPath -or $currentEnvPath -notcontains $sdkPath) {
    [System.Environment]::SetEnvironmentVariable($envVarName, $sdkPath, [System.EnvironmentVariableTarget]::Machine)
}

Write-Output "Level Zero SDK Path Setup completed successfully."