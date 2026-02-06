##
# Copyright (C) 2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

import os
import sys
import unittest
from ctypes import c_int32

# Add the source directory to Python path so we can import pyzes
script_dir = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(script_dir, "..", "..", "source")
source_dir = os.path.abspath(source_dir)
if source_dir not in sys.path:
    sys.path.insert(0, source_dir)


class TestUtilsInfrastructure(unittest.TestCase):
    """Test utility and infrastructure classes"""

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenPrintableStructureWhenConvertedToStringThenProvidesFormattedOutput(
        self,
    ):
        # Test _PrintableStructure string formatting functionality
        temp_state = self.pyzes.zes_temp_config_t()
        temp_state.enableCritical = True
        temp_state.threshold1 = 75.0
        temp_state.threshold2 = 80.0

        # Test string representation functionality
        str_repr = str(temp_state)
        self.assertIsInstance(str_repr, str)
        self.assertIn("zes_temp_config_t", str_repr)
        self.assertIn("enableCritical", str_repr)
        self.assertIn("threshold1", str_repr)

    def test_GivenPrintableStructureWithDefaultFormattingWhenConvertedToStringThenUsesDefaultFormat(
        self,
    ):
        # Test _PrintableStructure with <default> format case
        # Create a custom structure class with <default> formatting

        class TestStructure(self.pyzes._PrintableStructure):
            _fields_ = [("testField", c_int32)]
            _fmt_ = {
                "<default>": "default_%d"
            }  # This will trigger default format usage

        test_struct = TestStructure()
        test_struct.testField = 42

        str_repr = str(test_struct)
        self.assertIn("default_42", str_repr)  # Tests <default> format usage
        self.assertIn("TestStructure", str_repr)


if __name__ == "__main__":
    unittest.main()
