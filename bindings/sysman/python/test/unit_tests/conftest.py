##
# Copyright (C) 2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

"""
Pytest configuration for unit tests with GPU library mocking.
Unit tests should always use mocked GPU libraries to test logic in isolation.
"""

import sys
from unittest.mock import Mock, patch

import pytest


@pytest.fixture(autouse=True)
def mock_gpu_library():
    """
    Automatically mock the GPU library loading for all unit tests.
    Unit tests should always run with mocked libraries to test logic in isolation.
    """
    # Always mock for unit tests - no conditional logic needed
    with patch("ctypes.CDLL") as mock_cdll:
        # Create a mock library object
        mock_lib = Mock()
        mock_cdll.return_value = mock_lib

        # Patch the module before it gets imported
        if "pyzes" in sys.modules:
            # If already imported, patch the existing gpuLib
            import pyzes

            original_gpulib = pyzes.gpuLib
            pyzes.gpuLib = mock_lib
            yield mock_lib
            pyzes.gpuLib = original_gpulib
        else:
            # If not imported yet, let the mock handle the CDLL calls
            yield mock_lib
