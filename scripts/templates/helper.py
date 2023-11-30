"""
 Copyright (C) 2019-2021 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import re

"""
    Extracts traits from a spec object
"""
class obj_traits:

    @staticmethod
    def is_function(obj):
        try:
            return True if re.match(r"function", obj['type']) else False
        except:
            return False

    @staticmethod
    def is_function_with_input_handles(obj):
        try:
            if re.match(r"function", obj['type']):
                for param in obj['params']:
                    if param_traits.is_input(param) and type_traits.is_handle(param['type']):
                        return True
            return False
        except:
            return False

    @staticmethod
    def is_class(obj):
        try:
            return True if re.match(r"class", obj['type']) else False
        except:
            return False

    @staticmethod
    def is_experimental(obj):
        try:
            return True if re.search("Exp$", obj['name']) else False
        except:
            return False

    @staticmethod
    def class_name(obj):
        try:
            return obj['class']
        except:
            return None

"""
    Extracts traits from a class name
"""
class class_traits:

    @staticmethod
    def is_global(name, tags):
        try:
            return True if name in tags else False
        except:
            return False

    @staticmethod
    def is_namespace(name, namespace, tags):
        try:
            return tags[name] == namespace
        except:
            return False

    @staticmethod
    def is_singleton(item):
        try:
            return "singleton" == item['attribute']
        except:
            return False

    @staticmethod
    def get_handle(item, meta):
        try:
            return meta['class'][item['name']]['handle'][0]
        except:
            return ""

"""
    Extracts traits from a type name
"""
class type_traits:
    RE_HANDLE            = r"(.*)handle_t"
    RE_IPC               = r"(.*)ipc(.*)handle_t"
    RE_POINTER           = r"(.*\w+)\*+"
    RE_DESC              = r"(.*)desc_t.*"
    RE_PROPS             = r"(.*)properties_t.*"
    RE_FLAGS             = r"(.*)flags_t"
    RE_COUNTERS          = r"(.*)counters_t"
    RE_PORT_CONFIG       = r"(.*)port_config_t"
    RE_FAN_CONFIG        = r"(.*)fan_config_t"
    RE_RAS_CONFIG        = r"(.*)ras_config_t"
    RE_TEMP_CONFIG       = r"(.*)temp_config_t"
    RE_DEVICE_STATE      = r"(.*)device_state_t"
    RE_PROCESS_STATE     = r"(.*)process_state_t"
    RE_PCI_STATE         = r"(.*)pci_state_t"
    RE_FABRIC_PORT_STATE = r"(.*)fabric_port_state_t"
    RE_FREQ_STATE        = r"(.*)freq_state_t"
    RE_LED_STATE         = r"(.*)led_state_t"
    RE_MEM_STATE         = r"(.*)mem_state_t"
    RE_PSU_STATE         = r"(.*)psu_state_t"
    RE_RAS_STATE         = r"(.*)ras_state_t"
    RE_CAPABILITIES      = r"(.*)capabilities_t"
    RE_PROPS_EXP         = r"(.*)properties_exp_t"

    @staticmethod
    def base(name):
        return _remove_const_ptr(name)

    @classmethod
    def is_handle(cls, name):
        try:
            return True if re.match(cls.RE_HANDLE, name) else False
        except:
            return False

    @classmethod
    def is_ipc_handle(cls, name):
        try:
            return True if re.match(cls.RE_IPC, name) else False
        except:
            return False

    @staticmethod
    def is_class_handle(name, meta):
        try:
            name = _remove_const_ptr(name)
            return len(meta['handle'][name]['class']) > 0
        except:
            return False

    @classmethod
    def is_pointer(cls, name):
        try:
            return True if re.match(cls.RE_POINTER, name) else False
        except:
            return False

    @classmethod
    def is_descriptor(cls, name):
        try:
            return True if re.match(cls.RE_DESC, name) else False
        except:
            return False

    @classmethod
    def is_properties(cls, name):
        try:
            return True if re.match(cls.RE_PROPS, name) else False
        except:
            return False

    @classmethod
    def is_counters(cls, name):
        try:
            return True if re.match(cls.RE_COUNTERS, name) else False
        except:
            return False

    @classmethod
    def is_port_config(cls, name):
        try:
            return True if re.match(cls.RE_PORT_CONFIG, name) else False
        except:
            return False

    @classmethod
    def is_fan_config(cls, name):
        try:
            return True if re.match(cls.RE_FAN_CONFIG, name) else False
        except:
            return False

    @classmethod
    def is_ras_config(cls, name):
        try:
            return True if re.match(cls.RE_RAS_CONFIG, name) else False
        except:
            return False

    @classmethod
    def is_temp_config(cls, name):
        try:
            return True if re.match(cls.RE_TEMP_CONFIG, name) else False
        except:
            return False

    @classmethod
    def is_device_state(cls, name):
        try:
            return True if re.match(cls.RE_DEVICE_STATE, name) else False
        except:
            return False

    @classmethod
    def is_process_state(cls, name):
        try:
            return True if re.match(cls.RE_PROCESS_STATE, name) else False
        except:
            return False

    @classmethod
    def is_pci_state(cls, name):
        try:
            return True if re.match(cls.RE_PCI_STATE, name) else False
        except:
            return False

    @classmethod
    def is_fabric_port_state(cls, name):
        try:
            return True if re.match(cls.RE_FABRIC_PORT_STATE, name) else False
        except:
            return False

    @classmethod
    def is_freq_state(cls, name):
        try:
            return True if re.match(cls.RE_FREQ_STATE, name) else False
        except:
            return False

    @classmethod
    def is_led_state(cls, name):
        try:
            return True if re.match(cls.RE_LED_STATE, name) else False
        except:
            return False

    @classmethod
    def is_mem_state(cls, name):
        try:
            return True if re.match(cls.RE_MEM_STATE, name) else False
        except:
            return False

    @classmethod
    def is_psu_state(cls, name):
        try:
            return True if re.match(cls.RE_PSU_STATE, name) else False
        except:
            return False

    @classmethod
    def is_ras_state(cls, name):
        try:
            return True if re.match(cls.RE_RAS_STATE, name) else False
        except:
            return False

    @classmethod
    def is_properties_exp(cls, name):
        try:
            return True if re.match(cls.RE_PROPS_EXP, name) else False
        except:
            return False

    @classmethod
    def is_capabilities(cls, name):
        try:
            return True if re.match(cls.RE_CAPABILITIES, name) else False
        except:
            return False

    @classmethod
    def is_flags(cls, name):
        try:
            return True if re.match(cls.RE_FLAGS, name) else False
        except:
            return False

    @staticmethod
    def is_known(name, meta):
        try:
            name = _remove_const_ptr(name)
            for group in meta:
                if name in meta[group]:
                    return True
            return False
        except:
            return False

    @staticmethod
    def is_enum(name, meta):
        try:
            name = _remove_const_ptr(name)
            if name in meta['enum']:
                return True
            return False
        except:
            return False

    @staticmethod
    def is_struct(name, meta):
        try:
            name = _remove_const_ptr(name)
            if name in meta['struct']:
                return True
            return False
        except:
            return False

    @staticmethod
    def find_class_name(name, meta):
        try:
            name = _remove_const_ptr(name)
            for group in meta:
                if name in meta[group]:
                    return meta[group][name]['class']
            return None
        except:
            return None

"""
    Extracts traits from a value name
"""
class value_traits:
    RE_VERSION  = r"\$X_MAKE_VERSION\(\s*(\d+)\s*\,\s*(\d+)\s*\)"
    RE_BIT      = r".*BIT\(\s*(.*)\s*\)"
    RE_HEX      = r"0x\w+"
    RE_MACRO    = r"(\$\w+)\(.*\)"
    RE_ARRAY    = r"(.*)\[(.*)\]"

    @classmethod
    def is_ver(cls, name):
        try:
            return True if re.match(cls.RE_VERSION, name) else False
        except:
            return False

    @classmethod
    def get_major_ver(cls, name):
        try:
            return int(re.sub(cls.RE_VERSION, r"\1", name))
        except:
            return 0

    @classmethod
    def get_minor_ver(cls, name):
        try:
            return int(re.sub(cls.RE_VERSION, r"\2", name))
        except:
            return 0

    @classmethod
    def is_bit(cls, name):
        try:
            return True if re.match(cls.RE_BIT, name) else False
        except:
            return False

    @classmethod
    def get_bit_count(cls, name):
        try:
            return int(re.sub(cls.RE_BIT, r"\1", name))
        except:
            return 0

    @classmethod
    def is_hex(cls, name):
        try:
            return True if re.match(cls.RE_HEX, name) else False
        except:
            return False

    @classmethod
    def is_macro(cls, name, meta):
        try:
            name = cls.get_macro_name(name)
            name = cls.get_array_length(name)
            return True if name in meta['macro'] else False
        except:
            return False

    @classmethod
    def get_macro_name(cls, name):
        try:
            return re.sub(cls.RE_MACRO, r"\1", name)    # 'NAME()' -> 'NAME'
        except:
            return name

    @classmethod
    def is_array(cls, name):
        try:
            return True if re.match(cls.RE_ARRAY, name) else False
        except:
            return False

    @classmethod
    def get_array_name(cls, name):
        try:
            return re.sub(cls.RE_ARRAY, r"\1", name)    # 'name[len]' -> 'name'
        except:
            return name

    @classmethod
    def get_array_length(cls, name):
        try:
            return re.sub(cls.RE_ARRAY, r"\2", name)    # 'name[len]' -> 'len'
        except:
            return name

    @classmethod
    def find_enum_name(cls, name, meta):
        try:
            name = cls.get_array_name(name)
            # if the value is an etor, return the name of the enum
            for e in meta['enum']:
                if name in meta['enum'][e]['etors']:
                    return e
            return None
        except:
            return None

"""
    Extracts traits from a parameter object
"""
class param_traits:
    RE_MBZ      = r".*\[mbz\].*"
    RE_IN       = r"^\[in\].*"
    RE_OUT      = r"^\[out\].*"
    RE_INOUT    = r"^\[in,out\].*"
    RE_OPTIONAL = r".*\[optional\].*"
    RE_RANGE    = r".*\[range\((.+),\s*(.+)\)\][\S\s]*"
    RE_RELEASE  = r".*\[release\].*"

    @classmethod
    def is_mbz(cls, item):
        try:
            return True if re.match(cls.RE_MBZ, item['desc']) else False
        except:
            return False

    @classmethod
    def is_input(cls, item):
        try:
            return True if re.match(cls.RE_IN, item['desc']) else False
        except:
            return False

    @classmethod
    def is_output(cls, item):
        try:
            return True if re.match(cls.RE_OUT, item['desc']) else False
        except:
            return False

    @classmethod
    def is_inoutput(cls, item):
        try:
            return True if re.match(cls.RE_INOUT, item['desc']) else False
        except:
            return False

    @classmethod
    def is_optional(cls, item):
        try:
            return True if re.match(cls.RE_OPTIONAL, item['desc']) else False
        except:
            return False

    @classmethod
    def is_range(cls, item):
        try:
            return True if re.match(cls.RE_RANGE, item['desc']) else False
        except:
            return False

    @classmethod
    def range_start(cls, item):
        try:
            return re.sub(cls.RE_RANGE, r"\1", item['desc'])
        except:
            return None

    @classmethod
    def range_end(cls, item):
        try:
            return re.sub(cls.RE_RANGE, r"\2", item['desc'])
        except:
            return None
    @classmethod
    def is_release(cls, item):
        try:
            return True if re.match(cls.RE_RELEASE, item['desc']) else False
        except:
            return False

"""
    Extracts traits from a function object
"""
class function_traits:

    @staticmethod
    def is_static(item):
        try:
            return True if re.match(r"static", item['decl']) else False
        except:
            return False

    @staticmethod
    def is_global(item, tags):
        try:
            return True if item['class'] in tags else False
        except:
            return False

"""
Public:
    substitues each tag['key'] with tag['value']
    if cpp, then remove each tag['key'] if matches namespace
    if comment, then insert doxygen '::' notation at beginning (for autogen links)
"""
def subt(namespace, tags, string, comment=False, cpp=False, remove_namespace=False):
    for key, value in tags.items():
        if comment or not cpp:                                                  # generating c names
            string = re.sub(r"-%s"%re.escape(key), "-"+value, string)           # hack for compile options
            repl = "::"+value if comment and "$OneApi" != key else value        # replace tag; e.g., "$x" -> "xe"
            string = re.sub(re.escape(key), repl, string)
            string = re.sub(re.escape(key.upper()), repl.upper(), string)
        elif re.match(namespace, value):                                        # generating c++ names and tag matches current namespace
            repl = ""                                                           # remove tags; e.g., "$x" -> ""
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
        elif remove_namespace:                                                  # generating c++ names and tags do _not_ match current namespace
            repl = ""                                                           # remove namespace; e.g. "$x" -> ""
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
        else:                                                                   # generating c++ names and tags do _not_ match current namespace
            repl = value+"::"                                                   # add namespace; e.g. "$x" -> "xe::"
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
    return string

"""
Public:
    appends whitespace (in multiples of 4) to the end of the string,
    until len(string) > count
"""
def append_ws(string, count):
    while len(string) > count:
        count = count + 4
    string = '{str: <{width}}'.format(str=string, width=count)
    return string

"""
Public:
    split the line of text into a list of strings,
    where each length of each entry is less-than count
"""
def split_line(line, ch_count):
    if not line:
        return [""]

    RE_NEWLINE = r"(.*)\n(.*)"

    words           = line.split(" ")
    lines           = []
    word_list       = []

    for word in words:
        if re.match(RE_NEWLINE, word):
            prologue = re.sub(RE_NEWLINE,r"\1",word)
            epilogue = re.sub(RE_NEWLINE,r"\2",word)
            word_list.append(prologue)
            lines.append(" ".join(word_list))
            word_list = []
            if len(epilogue):
                word_list.append(epilogue)

        elif sum(map(len, word_list)) + len(word_list) + len(word) <= ch_count:
            word_list.append(word)

        else:
            lines.append(" ".join(word_list))
            word_list = [word]

    if len(word_list):
        lines.append(" ".join(word_list))
    return lines

"""
Private:
    converts string from camelCase to snake_case
"""
def _camel_to_snake(name):
    str = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    str = re.sub('([a-z0-9])([A-Z])', r'\1_\2', str).lower()
    return str

"""
Public:
    removes items from the list with the key and whose value do not match filter
"""
def filter_items(lst, key, filter):
    flst = []
    for item in lst:
        if key in item:
            if filter == item[key]:
                flst.append(item)
    return flst

"""
Public:
    returns a list of items with key from a list of dict
"""
def extract_items(lst, key):
    klst = []
    for item in lst:
        if key in item:
            klst.append(item[key])
    return klst

"""
Public:
    returns a list of all objects of type in all specs
"""
def extract_objs(specs, value):
    objs = []
    for s in specs:
        for obj in s['objects']:
            if re.match(value, obj['type']):
                objs.append(obj)
    return objs

"""
Private:
    removes 'const' from c++ type
"""
def _remove_const(name):
    name = name.split(" ")[-1]
    return name

"""
Private:
    removes '*' from c++ type
"""
def _remove_ptr(name, last=True):
    if last:
        name = re.sub(r"(.*)\*$", r"\1", name) # removes only last '*'
    else:
        name = re.sub(r"\*", "", name) # removes all '*'
    return name

"""
Private:
    removes 'const' and '*' from c++ type
"""
def _remove_const_ptr(name):
    name = _remove_ptr(_remove_const(name))
    return name

"""
Private:
    adds class name to type
    e.g., "const type*" -> "const cname::type*"
"""
def _add_class(name, cname):
    words = name.split(" ")
    words[-1] = "%s::%s"%(cname, words[-1])
    return " ".join(words)

"""
Private:
    removes class name from type
    e.g., "const cls_type*" -> "const type*"
"""
def _remove_class(name, cname, upper_case=False):
    if cname:
        cname = _camel_to_snake(cname)
        if upper_case:
            cname = cname.upper()
        RE_CLS = r"(.*)(%s_)(\w+)"%cname # remove "cls_" part
        if re.match(RE_CLS, name):
            name = re.sub(RE_CLS, r"\1\3", name)
    return name

"""
Public:
    returns c/c++ name of macro
"""
def make_macro_name(namespace, tags, obj, params=True):
    if params:
        return subt(namespace, tags, obj['name'])
    else:
        name = re.sub(r"(.*)\(.*", r"\1", obj['name'])  # remove '()' part
        return subt(namespace, tags, name)

"""
Public:
    returns c/c++ name of enums, structs, unions, typedefs...
"""
def make_type_name(namespace, tags, obj, cpp=False):
    name = subt(namespace, tags, obj['name'], cpp=cpp)

    # if c++, remove class part of name
    if cpp and 'class' in obj:
        cname = subt(namespace, tags, obj['class'], cpp=cpp)
        name = _remove_class(name, cname)
    return name

"""
Public:
    returns c/c++ name of enums...
"""
def make_enum_name(namespace, tags, obj, cpp=False):
    name = make_type_name(namespace, tags, obj, cpp)
    if type_traits.is_flags(obj['name']):
        name = re.sub(r"flags", r"flag", name)
    return name

"""
Public:
    returns c/c++ name of etor
"""
def make_etor_name(namespace, tags, enum, etor, cpp=False, py=False, meta=None):
    if cpp or py:
        # if c++, remove the verbose enum part of the etor
        if type_traits.is_flags(enum) and not py:
            # e.g., "CLS_ENUM_NAME_ETOR_NAME" -> "ENUM_NAME_ETOR_NAME"
            cname = type_traits.find_class_name(enum, meta)
            cname = subt(namespace, tags, cname, cpp=cpp)
            name = subt(namespace, tags, etor, cpp=cpp)
            name = _remove_class(name, cname, upper_case=True)
        else:
            # e.g., "ENUM_NAME_ETOR_NAME" -> "ETOR_NAME"
            if type_traits.is_flags(enum):
                prefix = re.sub(r"(\w+)_flags_t", r"\1_flag", subt(namespace, tags, enum, cpp=cpp)).upper()
            else:
                prefix = re.sub(r"(\w+)_t", r"\1", subt(namespace, tags, enum, cpp=cpp)).upper()
            name = re.sub(r"%s_(\w+)"%prefix, r"\1", subt(namespace, tags, etor, cpp=cpp))
            name = re.sub(r"^(\d+\w*)", r"_\1", name)
    else:
        name = subt(namespace, tags, etor, cpp=cpp)
    return name

"""
Private:
    returns c/c++ name of value
"""
def _get_value_name(namespace, tags, value, cpp, meta, is_array_size=False, cbase=None):
    if cpp:
        if value_traits.is_macro(value, meta):
            value = subt(namespace, tags, value)
        else:
            name = value_traits.find_enum_name(value, meta)
            if name:
                # e.g., "ETOR_NAME" -> "ENUM_NAME::ETOR_NAME"
                enum = subt(namespace, tags, name, cpp=cpp)
                # e.g., "CLS_ENUM_NAME" -> "ENUM_NAME"
                cname = type_traits.find_class_name(name, meta)
                cname = subt(namespace, tags, cname, cpp=cpp)
                enum = _remove_class(enum, cname)
                if cname and cbase:
                    cbase = subt(namespace, tags, cbase, cpp=cpp)
                    if cbase == cname:
                        enum = _remove_class(enum, cname)
                    else:
                        enum = "%s::%s"%(cname, enum)
                if is_array_size:
                    value = "static_cast<int>(%s::%s)"%(enum, make_etor_name(namespace, tags, name, value, cpp=cpp, meta=meta))
                else:
                    value = "%s::%s"%(enum, make_etor_name(namespace, tags, name, value, cpp=cpp, meta=meta))
            else:
                value = subt(namespace, tags, value, cpp=cpp)
    else:
        value = subt(namespace, tags, value, cpp=cpp)
    return value

"""
Public:
    returns a list of strings for declaring each enumerator in an enumeration
    c++ format: "ETOR_NAME = VALUE, ///< DESCRIPTION"
    python format: "ETOR_NAME = VALUE, ## DESCRIPTION"
"""
def make_etor_lines(namespace, tags, obj, cpp=False, py=False, meta=None):
    lines = []
    for item in obj['etors']:
        name = make_etor_name(namespace, tags, obj['name'], item['name'], cpp, py, meta)

        if 'value' in item:
            delim = "," if not py else ""
            value = _get_value_name(namespace, tags, item['value'], cpp, meta, cbase=obj_traits.class_name(obj))
            prologue = "%s = %s%s"%(name, value, delim)
        elif py:
            prologue = "%s = auto()"%(name)
        else:
            prologue = "%s,"%(name)

        comment_style = "##" if py else "///<"
        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s%s %s"%(append_ws(prologue, 48), comment_style, line))
            prologue = ""

    if cpp and not type_traits.is_flags(obj['name']):
        lines.append("FORCE_UINT32 = 0x7fffffff")
    elif not py:
        lines.append("%sFORCE_UINT32 = 0x7fffffff"%make_enum_name(namespace, tags, obj, cpp)[:-1].upper())

    return lines

"""
Public:
    determines whether the enumeration represents a bitfield
"""
def is_enum_bitfield(obj):
    for item in obj['etors']:
        if 'value' in item and value_traits.is_bit(item['value']):
            return True
    return False

"""
Public:
    returns c/c++ name of any type
"""
def get_type_name(namespace, tags, obj, item, cpp=False, meta=None, handle_to_class=True):
    name = subt(namespace, tags, item, cpp=cpp)
    if cpp:
        cname = type_traits.find_class_name(item, meta)
        if cname:
            is_global = class_traits.is_global(cname, tags)
            is_namespace = class_traits.is_namespace(cname, namespace, tags)  # cname == namespace? e.g., cname == "$x"
            is_handle = type_traits.is_handle(item)

            is_inscope = False
            if obj_traits.is_class(obj):                        # if the obj _is_ a class
                is_inscope = cname == obj['name']                   # then is the item's class this obj?
            elif not is_global:                                 # else if the obj belongs to a class
                is_inscope = cname == obj_traits.class_name(obj)    # then is the item's class the same as the obj?

            cname_no_namespace = subt(namespace, tags, cname, cpp=cpp, remove_namespace=True)
            cname = subt(namespace, tags, cname, cpp=cpp)   # remove tags from class name

            if not (is_global or is_namespace or is_handle or is_inscope):
                # need to prepend the class name to the type after removing namespace from the type
                name = subt(namespace, tags, item, cpp=cpp, remove_namespace=True)
                name = _remove_class(name, cname_no_namespace)
                name = _add_class(name, cname)

            elif handle_to_class and is_handle and not obj_traits.is_class(obj):
                # convert handles to class pointers
                name = re.sub(r"(const\s*)?(\w*:?:?\w+)(\**)", r"\1%s*\3"%cname, name) # e.g., const name* -> const cname**

            if not is_handle:
                # remove the verbose class part from the type name
                name = _remove_class(name, cname)

    return name

"""
Private:
    returns c/c++ name of any type
"""
def _get_type_name(namespace, tags, obj, item, cpp=False, meta=None, handle_to_class=True):
    return get_type_name(namespace, tags, obj, item['type'], cpp, meta, handle_to_class)

"""
Private:
    returns python c_type name of any type
"""
def get_ctype_name(namespace, tags, item):
    name = subt(namespace, tags, item['type'])
    name = _remove_const(name)
    name = re.sub(r"void\*", "c_void_p", name)
    name = re.sub(r"char\*", "c_char_p", name)
    name = re.sub(r"uint8_t", "c_ubyte", name)
    name = re.sub(r"uint16_t", "c_ushort", name)
    name = re.sub(r"uint32_t", "c_ulong", name)
    name = re.sub(r"uint64_t", "c_ulonglong", name)
    name = re.sub(r"size_t", "c_size_t", name)
    name = re.sub(r"float", "c_float", name)
    name = re.sub(r"double", "c_double", name)
    name = re.sub(r"\bchar", "c_char", name)
    name = re.sub(r"\bint", "c_int", name)

    if type_traits.is_pointer(name):
        name = _remove_ptr(name)
        name = "POINTER(%s)"%name

    elif 'name' in item and value_traits.is_array(item['name']):
        length = subt(namespace, tags, value_traits.get_array_length(item['name']))
        name = "%s * %s"%(name, length)

    return name

"""
Public:
    returns c/c++ name of member of struct/class
"""
def make_member_name(namespace, tags, item, prefix="", cpp=False, meta=None, remove_array=False, cbase=None):
    if cpp and value_traits.is_macro(item['name'], meta):
        name = subt(namespace, tags, item['name'])
    elif cpp and value_traits.is_array(item['name']):
        name = value_traits.get_array_name(item['name'])
        name = subt(namespace, tags, name)
        alength = value_traits.get_array_length(item['name'])
        alength = _get_value_name(namespace, tags, alength, cpp, meta, is_array_size=True, cbase=cbase)
        name = "%s[%s]"%(name, alength)
    else:
        name = subt(namespace, tags, prefix+item['name'], cpp=cpp)

    if remove_array:
        name = value_traits.get_array_name(name)

    return name

"""
Public:
    returns a list of strings for each member of a structure or class
    c++ format: "TYPE NAME = INIT, ///< DESCRIPTION"
    python format: "("NAME", TYPE)" ## DESCRIPTION"
"""
def make_member_lines(namespace, tags, obj, prefix="", cpp=False, py=False, meta=None):
    lines = []
    if 'members' not in obj:
        return lines

    for i, item in enumerate(obj['members']):
        name = make_member_name(namespace, tags, item, prefix, cpp, meta, remove_array=py, cbase=obj_traits.class_name(obj))

        if py:
            tname = get_ctype_name(namespace, tags, item)
        else:
            tname = _get_type_name(namespace, tags, obj, item, cpp, meta)

        if cpp and 'init' in item:
            value = _get_value_name(namespace, tags, item['init'], cpp, meta, cbase=obj_traits.class_name(obj))
            prologue = "%s %s = %s;"%(tname, name, value)
        elif py:
            delim = "," if i < (len(obj['members'])-1) else ""
            prologue = "(\"%s\", %s)%s"%(name, tname, delim)
        else:
            prologue = "%s %s;"%(tname, name)

        comment_style = "##" if py else "///<"
        ws_count = 64 if py else 48
        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s%s %s"%(append_ws(prologue, ws_count), comment_style, line))
            prologue = ""
    return lines

"""
Public:
    returns a list of c++ strings for each member of a class
    format: "auto getNAME( void ) const { return MEMBER; }"
"""
def make_member_function_lines(namespace, tags, obj, prefix=""):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        name = subt(namespace, tags, item['name'], cpp=True)

        is_pointer = type_traits.is_pointer(item['type'])
        if is_pointer and re.match(r"p\w+", name):  # if this is a pointer and starts with 'p',
            fname = name[1:].title()                # then remove the 'p' part of the name
        else:
            fname = name.title()

        lines.append("auto get%s( void ) const { return %s; }"%(fname, prefix+name))
    return lines

"""
Private:
    returns the list of parameters, filtering based on desc tags
"""
def _filter_param_list(params, filters1=["[in]", "[in,out]", "[out]"], filters2=[""]):
    lst = []
    for p in params:
        for f1 in filters1:
            if f1 in p['desc']:
                for f2 in filters2:
                    if f2 in p['desc']:
                        lst.append(p)
                        break
                break
    return lst

"""
Private:
    returns c/c++ name of parameter
"""
def _get_param_name(namespace, tags, item, cpp):
    name = subt(namespace, tags, item['name'], cpp=cpp)
    if cpp and type_traits.is_handle(item['type']):
        name = re.sub(r"\bh([A-Z]\w+)", r"p\1", name) # change "hName" to "pName"
        name = re.sub(r"\bph([A-Z]\w+)", r"pp\1", name) # change "phName" to "ppName"
        if param_traits.is_output(item) and not param_traits.is_optional(item):
            name = re.sub(r"p(p[A-Z]\w+)", r"\1", name) #change ppName to pName
    return name



def get_func_descs(namespace, tags, obj):
    descs = []
    for item in obj['params']:
        if (    type_traits.is_descriptor(item['type']) or
                type_traits.is_properties(item['type']) or
                type_traits.is_counters(item['type']) or
                type_traits.is_port_config(item['type']) or
                type_traits.is_fan_config(item['type']) or
                type_traits.is_ras_config(item['type']) or
                type_traits.is_temp_config(item['type']) or
                type_traits.is_device_state(item['type']) or
                type_traits.is_process_state(item['type']) or
                type_traits.is_pci_state(item['type']) or
                type_traits.is_fabric_port_state(item['type']) or
                type_traits.is_freq_state(item['type']) or
                type_traits.is_led_state(item['type']) or
                type_traits.is_mem_state(item['type']) or
                type_traits.is_psu_state(item['type']) or
                type_traits.is_ras_state(item['type']) or
                type_traits.is_capabilities(item['type']) or
                type_traits.is_properties_exp(item['type'])):
            name = _get_param_name(namespace, tags, item, False)
            descs.append(name)

    return descs

"""
Public:
    returns a list of c++ strings for each parameter of a function
    format: "TYPE NAME = INIT, ///< DESCRIPTION"
"""
def make_param_lines(namespace, tags, obj, cpp=False, py=False, decl=False, meta=None, format=["type", "name", "init", "delim", "desc"], delim=","):
    lines = []

    if cpp:
        is_static = function_traits.is_static(obj)
        is_global = function_traits.is_global(obj, tags)
        params = obj['params'] if is_static or is_global else obj['params'][1:]
        params = _filter_param_list(params, ["[in]", "[in,out]"]) + _filter_param_list(params, ["[out]"], ["[optional"])
    else:
        params = obj['params']

    for i, item in enumerate(params):
        name = _get_param_name(namespace, tags, item, cpp=cpp)
        if py:
            tname = get_ctype_name(namespace, tags, item)
        else:
            tname = _get_type_name(namespace, tags, obj, item, cpp, meta)
        init = ""
        local = "Local" if type_traits.is_pointer(item['type']) and type_traits.is_handle(item['type']) and param_traits.is_input(item) else ""

        if cpp:
            if decl and param_traits.is_optional(item):
                is_pointer = type_traits.is_pointer(item['type'])
                is_handle = type_traits.is_handle(item['type'])
                if is_pointer or is_handle:
                    init += "= nullptr"
                else:
                    init += "= 0"

        words = []
        if "local" in format:
            name += local
        if "type*" in format:
            words.append(tname+"*")
            name = "p"+name
        elif "type" in format:
            words.append(tname)
        if "name" in format:
            words.append(name)
        if "init" in format and len(init) > 0:
            words.append(init)

        prologue = " ".join(words)
        if "delim" in format:
            if i < len(params)-1:
                prologue += delim

        if "desc" in format:
            desc = item['desc']
            if cpp:
                desc = re.sub(r"handle of", r"pointer to", desc)
            for line in split_line(subt(namespace, tags, desc, True, cpp), 70):
                lines.append("%s///< %s"%(append_ws(prologue, 48), line))
                prologue = ""
        else:
            lines.append(prologue)

    if "type" in format and len(lines) == 0 and not py:
        lines = ["void"]
    return lines

"""
Public:
    returns a string of c++ template parameters
    format: "TPARAM0, TPARAM1"
"""
def make_tparams_line(namespace, tags, obj):
    line = ", ".join(obj['tparams'])
    return subt(namespace, tags, line, cpp=True)

"""
Public:
    returns True if ctor has parameters
"""
def has_ctor_params(obj):
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    return len(params) > 0

"""
Public:
    returns a list of c++ strings for ctor parameters of members
    format: "TYPE NAME, ///< DESCRIPTION"
"""
def make_ctor_param_lines(namespace, tags, obj, meta=None, format=["type", "name", "delim", "desc"]):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])
        tname = _get_type_name(namespace, tags, obj, item, True, meta)

        if type_traits.is_descriptor(tname):
            tname = "const %s*"%tname # e.g., "xe_event_desc_t*" -> "const desc_t*"

        words = []
        if "type" in format:
            words.append(tname)
        if "name" in format:
            words.append(name)

        prologue = " ".join(words)
        if "delim" in format:
            if i < len(params)-1:
                prologue += ","

        if "desc" in format:
            for line in split_line(subt(namespace, tags, item['desc'], True), 70):
                lines.append("%s///< %s"%(append_ws(prologue, 48), line))
                prologue = ""
        else:
            lines.append(prologue)

    if "type" in format and len(lines) == 0:
        lines = ["void"]
    return lines

"""
Public:
    returns a list of c++ strings for initializing members from ctor parameters of members
    format: "MEMBER( NAME ),"
"""
def make_ctor_param_init_lines(namespace, tags, obj, prefix="", meta=None):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])
        tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta)

        member = prefix+name
        if type_traits.is_descriptor(tname):
            name = "( %s ) ? *%s : desc_t{}"%(name, name)

        delim = "," if i < len(params)-1 else ""
        lines.append("%s( %s )%s"%(member, name, delim))

    return lines

"""
Private:
    returns c/c++ name of local variable from parameter name
"""
def _get_local_name(name):
    name = re.sub(r"\bp([A-Z]\w+)", r"\1", name) # change pName to Name
    name = re.sub(r"\bp([hA-Z]\w+)", r"\1", name) # change phName to hName
    name = re.sub(r"\bp(p[A-Z]\w+)", r"\1", name) # change ppName to pName
    name = name[0].lower() + name[1:] # change Name to name
    return name

"""
Public:
    returns a list of dict for declaring local variables in c++ wrapper
"""
def make_wrapper_params(namespace, tags, obj, meta, specs):
    params = []
    returns = []
    numSelf = 0

    # if the input parameter is a class,
    # then need to use getHandle
    # if the input parameter is an array of classes
    # then need to create a std::vector of handles

    # if the output parameter is a class,
    # then need to create a local handle then call the ctor
    # if the output parameter is an array of classes
    # then need to create a std::vector to receive handles(s) then call the ctor for each

    # if the parameter is an input and the cpp type is different than the c type,
    # then need to use static_cast or reinterpret_cast

    # if the parameter is an output
    # then need to create a local variable

    is_static = function_traits.is_static(obj)
    is_global = function_traits.is_global(obj, tags)

    for i, item in enumerate(obj['params']):
        c_name = _get_param_name(namespace, tags, item, cpp=False)
        cpp_name = _get_param_name(namespace, tags, item, cpp=True)

        c_tname = _get_type_name(namespace, tags, obj, item, cpp=False, meta=meta)
        cpp_tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta, handle_to_class=False)
        cpp_cname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta)

        local_name = _get_local_name(c_name)

        if param_traits.is_range(item):
            range_start = param_traits.range_start(item)
            range_end   = param_traits.range_end(item)
            if type_traits.is_class_handle(item['type'], meta):
                if param_traits.is_output(item) or param_traits.is_inoutput(item):
                    if param_traits.is_optional(item):
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'range': (range_start, range_end),
                            'optional': True,
                            'arg': "%s.data()"%(local_name),
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': _make_ctor(namespace, tags, item, obj, meta, specs),
                            'name': cpp_name
                        })
                    else:
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'range': (range_start, range_end),
                            'optional': False,
                            'arg': "%s.data()"%(local_name),
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': _make_ctor(namespace, tags, item, obj, meta, specs),
                            'name': cpp_name
                        })
                        if param_traits.is_output(item):
                            returns.append(cpp_name)

                elif param_traits.is_optional(item):
                    params.append({
                        'local': local_name,
                        'ctype': _remove_const_ptr(c_tname),
                        'cpptype': _remove_const_ptr(cpp_tname),
                        'range': (range_start, range_end),
                        'init': cpp_name,
                        'optional': True,
                        'arg': "%s.data()"%(local_name)
                    })
                else:
                    params.append({
                        'local': local_name,
                        'ctype': _remove_const_ptr(c_tname),
                        'cpptype': _remove_const_ptr(cpp_tname),
                        'range': (range_start, range_end),
                        'init': cpp_name,
                        'optional': False,
                        'arg': "%s.data()"%(local_name)
                    })

            elif param_traits.is_output(item):
                params.append({
                    'local': local_name,
                    'ctype': _remove_const_ptr(c_tname),
                    'cpptype': _remove_const_ptr(cpp_tname),
                    'range': (range_start, range_end),
                    'optional': param_traits.is_optional(item),
                    'arg': "%s.data()"%(local_name)
                })
                returns.append(cpp_name)

            elif c_tname != cpp_tname:
                params.append({
                    'arg': "reinterpret_cast<%s>( %s )"%(c_tname, cpp_name)
                })

            else:
                params.append({
                    'arg': cpp_name
                })

        else:
            if type_traits.is_class_handle(item['type'], meta):
                is_this_handle = type_traits.find_class_name(item['type'], meta) == obj_traits.class_name(obj)
                if param_traits.is_output(item):
                    if param_traits.is_optional(item):
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'optional': True,
                            'arg': "( %s ) ? &%s : nullptr"%(cpp_name, local_name),
                            'release': False,
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': _make_ctor(namespace, tags, item, obj, meta, specs),
                            'name': cpp_name
                        })
                    else:
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'optional': False,
                            'arg': "&%s"%(local_name),
                            'release': False,
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': _make_ctor(namespace, tags, item, obj, meta, specs),
                            'name': cpp_name
                        })
                        returns.append(cpp_name)
                elif param_traits.is_optional(item):
                    params.append({
                        'arg': "( %s ) ? reinterpret_cast<%s>( %s->getHandle() ) : nullptr"%(cpp_name, c_tname, cpp_name)
                    })
                elif (not is_static and not is_global) and is_this_handle:
                    numSelf += 1
                    if numSelf == 1:
                        params.append({
                            'arg': "reinterpret_cast<%s>( getHandle() )"%(c_tname)
                        })
                    else:
                        params.append({
                            'arg': "reinterpret_cast<%s>( %s->getHandle() )"%(c_tname, cpp_name)
                        })
                elif param_traits.is_release(item):
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s->getHandle() )"%(c_tname, cpp_name),
                        'release': True,
                        'class': _remove_ptr(cpp_cname, False),
                        'name': cpp_name
                    })
                else:
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s->getHandle() )"%(c_tname, cpp_name)
                    })

            elif param_traits.is_output(item):
                params.append({
                    'local': local_name,
                    'ctype': _remove_const_ptr(c_tname),
                    'cpptype': _remove_const_ptr(cpp_tname),
                    'arg': "&%s"%(local_name),
                    'name': local_name
                })
                if c_tname != cpp_tname:
                    if type_traits.is_pointer(_remove_ptr(item['type'])) or (type_traits.is_handle(item['type']) and not type_traits.is_ipc_handle(item['type'])):
                        returns.append("reinterpret_cast<%s>( %s )"%(_remove_const_ptr(cpp_tname), local_name))
                    else:
                        returns.append("*reinterpret_cast<%s*>( &%s )"%(_remove_const_ptr(cpp_tname), local_name))
                else:
                    returns.append(local_name)

            elif c_tname != cpp_tname:
                if type_traits.is_ipc_handle(item['type']):
                    params.append({
                        'arg': "*reinterpret_cast<%s*>( &%s )"%(c_tname, cpp_name)
                    })
                elif type_traits.is_pointer(item['type']) or type_traits.is_handle(item['type']):
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s )"%(c_tname, cpp_name)
                    })
                elif type_traits.is_struct(item['type'], meta):
                    params.append({
                        'arg': "*reinterpret_cast<%s*>( &%s )"%(c_tname, cpp_name)
                    })
                else:
                    params.append({
                        'arg': "static_cast<%s>( %s )"%(c_tname, cpp_name)
                    })

            else:
                params.append({
                    'arg': cpp_name
                })

    if len(returns) == 0:
        rvalue = ""
    elif len(returns) > 1:
        rvalue = "std::make_tuple( %s )"%", ".join(returns)
    else:
        rvalue = "%s"%returns[0]

    return params, rvalue

"""
Private:
    returns a ctor dict in c++ wrapper
"""
def _make_ctor(namespace, tags, item, obj, meta, specs):
    cobj = next(iter(filter_items(extract_objs(specs, 'class'), 'name', type_traits.find_class_name(item['type'], meta))), None)
    is_singleton = class_traits.is_singleton(cobj)
    fty_name = "g_%sFactory"%make_class_name(namespace, tags, cobj)

    if obj_traits.class_name(obj) in meta['class'][cobj['name']].get('child',[]):
        cobj2 = next(iter(filter_items(extract_objs(specs, 'class'), 'name', obj_traits.class_name(obj))), None)
        is_singleton = class_traits.is_singleton(cobj2)
        fty_name = "g_%sFactory"%make_class_name(namespace, tags, cobj2)

    return {
        'params': _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta),
        'factory': fty_name if is_singleton else ""
        }

"""
Private:
    returns a list of c++ strings of ctor arguments in c++ wrapper
"""
def _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta):
    params = []

    is_static = function_traits.is_static(obj)
    is_global = function_traits.is_global(obj, tags)

    # generate list of names for each parameter of the current function
    oparams = [ _get_param_name(namespace, tags, oparam, cpp=True) for oparam in obj['params'] ]

    # walk the ctor parameter names
    cparams = make_ctor_param_lines(namespace, tags, cobj, meta=meta, format=['name'])
    for i, name in enumerate(cparams):
        if name == "handle":
            c_name = _get_param_name(namespace, tags, item, cpp=False)
            local_name = _get_local_name(c_name)

            cpp_tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta, handle_to_class=False)

            if param_traits.is_range(item):
                params.append("reinterpret_cast<%s>( %s[ i ] )"%(_remove_const_ptr(cpp_tname), local_name))
            else:
                params.append("reinterpret_cast<%s>( %s )"%(_remove_const_ptr(cpp_tname), local_name))

        elif name in oparams:
            if (not is_static and not is_global) and (0 == oparams.index(name)):
                params.append("this")
            else:
                params.append(name)

        else:
            if (not is_static and not is_global):
                params.append("m_"+name)
            else:
                params.append("nullptr")

    return params

"""
Public:
    returns a list of strings for the description
    format: "@brief DESCRIPTION"
"""
def make_desc_lines(namespace, tags, obj, cpp=False):
    lines = []
    prologue = "@brief"
    for line in split_line(subt(namespace, tags, obj['desc'], True, cpp), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

"""
Public:
    returns a list of strings for the detailed description
    format: "@details DESCRIPTION"
"""
def make_details_lines(namespace, tags, obj, cpp=False):
    lines = []
    if 'details' in obj:
        lines.append("")
        lines.append("@details")

        for item in obj['details']:
            if isinstance(item, dict):
                for key, values in item.items():
                    prologue = "    -"
                    for line in split_line(subt(namespace, tags, key, True, cpp), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
                    for val in values:
                        prologue = "        +"
                        for line in split_line(subt(namespace, tags, val, True, cpp), 66):
                            lines.append("%s %s"%(prologue, line))
                            prologue = "         "
            else:
                prologue = "    -"
                for line in split_line(subt(namespace, tags, item, True, cpp), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
    if 'analogue' in obj:
        lines.append("")
        lines.append("@remarks")
        lines.append("  _Analogues_")
        for line in obj['analogue']:
            lines.append("    - %s"%line)
    return lines

"""
Public:
    returns a dict of auto-generated c++ parameter validation checks
"""
def make_param_checks(namespace, tags, obj, cpp=False, meta=None):
    checks = {}
    for item in obj.get('returns', []):
        for key, values in item.items():
            key = subt(namespace, tags, key, False, cpp)
            for val in values:
                code = re.match(r"^\`(.*)\`$", val)
                if code:
                    if key not in checks:
                        checks[key] = []
                    checks[key].append(subt(namespace, tags, code.group(1), False, cpp))
    return checks

"""
Public:
    returns a list of strings for possible return values
"""
def make_returns_lines(namespace, tags, obj, cpp=False, meta=None):
    lines = []
    if cpp:
        params = _filter_param_list(obj['params'], ["[out]"])
        if len(params) > 0:
            lines.append("@returns")
            for p in params:
                desc = re.sub(r"\[.*\](.*)", r"\1", p['desc'])
                tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
                lines.append("    - %s"%subt(namespace, tags, "%s:%s"%(tname, desc), True, cpp))
            lines.append("")
        for item in obj.get('returns', []):
            for key, values in item.items():
                if "$X_RESULT_NOT_READY" == key:
                    if len(lines) == 0:
                        lines.append("@returns")
                    lines.append("    - %s"%subt(namespace, tags, "$x_bool_t:'0' when $X_RESULT_NOT_READY", cpp=cpp))
        lines.append("@throws result_t")

    else:
        lines.append("@returns")
        for item in obj.get('returns', []):
            for key, values in item.items():
                lines.append("    - %s"%subt(namespace, tags, key, True, cpp))
                for val in values:
                    lines.append("        + %s"%subt(namespace, tags, val, True, cpp))

    return lines

"""
Public:
    returns c++ string for declaring function return type
"""
def make_return_type(namespace, tags, obj, cpp=False, decl=False, meta=None):
    # only "return" the parameters declared as "out"
    params = _filter_param_list(obj['params'], ["[out]"])

    types = []
    for p in params:
        if not param_traits.is_optional(p):
            tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
            if cpp:
                cname = type_traits.find_class_name(p['type'], meta)
                is_handle = type_traits.is_handle(p['type'])

                if cname and not decl and not is_handle:
                    # need to prepend the class name to the type
                    tname = _add_class(tname, subt(namespace, tags, cname, cpp=cpp))

                elif cname and is_handle:
                    # convert handles to class pointers
                    tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))

            types.append(tname)

    for item in obj.get('returns', []):
        for key, values in item.items():
            if "$X_RESULT_NOT_READY" == key:
                types.append(subt(namespace, tags, "$x_bool_t", cpp=cpp))

    if len(types) == 0:
        # if none exist, then just return "void"
        return "void"
    elif len(types) > 1:
        # if more than one return value, then return a tuple of values
        return "std::tuple<%s>"%", ".join(types)
    else:
        return types[0]

"""
Public:
    returns the name of a function
"""
def make_func_name(namespace, tags, obj, cpp=False):
    if not cpp:
        cname = obj_traits.class_name(obj)
    else:
        cname = ""
    return subt(namespace, tags, "%s%s"%(cname, obj['name']), cpp=cpp)

"""
Public:
    returns the name of a function
"""
def make_tracing_func_name(namespace, tags, obj):
    cname = obj_traits.class_name(obj)
    x_tag = tags['$x']
    tags['$x'] = '' #temporaly remove namespace tag so funx doesn't contain "ze"
    fname =  subt(namespace, tags, "%s%s"%(cname, obj['name']), cpp=False)
    fname = "zelTracer" + fname + "RegisterCallback" 
    tags['$x'] = x_tag
    return fname



"""
Public:
    returns the name of a function pointer
"""
def make_pfn_name(namespace, tags, obj):

    return subt(namespace, tags, "pfn%s"%obj['name'])

"""
Public:
    returns the name of a function pointer
"""
def make_pfncb_name(namespace, tags, obj):

    return subt(namespace, tags, "pfn%sCb"%obj['name'])

"""
Public:
    returns the name of a function pointer
"""
def make_pfn_type(namespace, tags, obj, epilogue=""):
    newtags = dict()
    for key, value in tags.items():
        if re.match(namespace, value):
            newtags[key] = "pfn"
    return "%s_%s%s_t"%(namespace, make_func_name(namespace, newtags, obj), epilogue)

"""
Public:
    returns the name of a function pointer
"""
def make_pfncb_type(namespace, tags, obj):

    return make_pfn_type(namespace, tags, obj, epilogue="Cb")

"""
Public:
    returns the name of a function pointer
"""
def make_pfncb_param_type(namespace, tags, obj):

    return "%s_params_t"%_camel_to_snake(make_func_name(namespace, tags, obj))

"""
Public:
    returns the name of a class
"""
def make_class_name(namespace, tags, obj):
    name = subt(namespace, tags, obj['name'], cpp=True)
    return name

"""
Public:
    returns a c++ string for the declaration of a base class
"""
def make_baseclass_decl(namespace, tags, obj):
    if 'base' in obj:
        return " : public %s"%(subt(namespace, tags, obj['base'], cpp=True))
    return ""

"""
Public:
    returns a c++ string for the declaration of a base class ctor
"""
def make_baseclass_ctor(namespace, tags, obj):
    base = subt(namespace, tags, obj['base'], cpp=True)
    ctor = base.split("::")[-1]
    return "%s::%s"%(base, ctor)

"""
Public:
    returns a list of all function objs for the specified class and version
"""
def get_class_function_objs(specs, cname, minVersion = 0, maxVersion = 9999):
    objects = []
    for s in specs:
        for obj in s['objects']:
            is_function = obj_traits.is_function(obj)
            match_cls = cname == obj_traits.class_name(obj)
            if is_function and match_cls:
                func_ver = float(obj.get('version',"1.0"))
                if func_ver <= maxVersion and func_ver >= minVersion:
                    objects.append(obj)
    return sorted(objects, key=lambda obj: (float(obj.get('version',"1.0"))*10000) + int(obj.get('ordinal',"100")))

"""
Public:
    returns a list of all non-experimental function objs and a list of experimental function objs for the specified class
"""
def get_class_function_objs_exp(specs, cname):
    objects = []
    exp_objects = []
    for s in specs:
        for obj in s['objects']:
            is_function = obj_traits.is_function(obj)
            match_cls = cname == obj_traits.class_name(obj)
            if is_function and match_cls:
                if obj_traits.is_experimental(obj):
                    exp_objects.append(obj)
                else:
                    objects.append(obj)
    objects = sorted(objects, key=lambda obj: (float(obj.get('version',"1.0"))*10000) + int(obj.get('ordinal',"100")))
    exp_objects = sorted(exp_objects, key=lambda obj: (float(obj.get('version',"1.0"))*10000) + int(obj.get('ordinal',"100")))              
    return objects, exp_objects


"""
Public:
    returns string name of DDI table for function object
"""
def get_table_name(namespace, tags, obj):
    cname = obj_traits.class_name(obj)
    if obj_traits.is_experimental(obj):
        cname=cname+"Exp"
    name = subt(namespace, tags, cname, cpp=True) # i.e., "$x" -> ""
    name = name if len(name) > 0 else "Global"
    return name

"""
Public:
    returns string name of callback table for function object
"""
def get_callback_table_name(namespace, tags, obj):
    cname = obj_traits.class_name(obj)
    name = subt(namespace, tags, cname, cpp=True) # i.e., "$x" -> ""
    name = name if len(name) > 0 else "Global"
    return name

"""
Public:
    returns a list of dict of each pfntables needed
"""
def get_pfntables(specs, meta, namespace, tags):
    tables = []
    for cname in sorted(meta['class'], key=lambda x: meta['class'][x]['ordinal']):
        objs, exp_objs = get_class_function_objs_exp(specs, cname)
        if len(objs) > 0:
            name = get_table_name(namespace, tags, objs[0])
            table = "%s_%s_dditable_t"%(namespace, _camel_to_snake(name))

            params = []
            params.append({
                'type': "$x_api_version_t",
                'name': "version",
                'desc': "[in] API version requested"
                })
            params.append({
                'type': "%s*"%table,
                'name': "pDdiTable",
                'desc': "[in,out] pointer to table of DDI function pointers"
                })
            export = {
                'name': "%sGet%sProcAddrTable"%(namespace, name),
                'params': params
                }

            pfn = "%s_pfnGet%sProcAddrTable_t"%(namespace, name)

            tables.append({
                'name': name, 
                'type': table,
                'export': export,
                'pfn': pfn,
                'functions': objs,
                'experimental': False
            })
        if len(exp_objs) > 0:
            name = get_table_name(namespace, tags, exp_objs[0])
            table = "%s_%s_dditable_t"%(namespace, _camel_to_snake(name))

            params = []
            params.append({
                'type': "$x_api_version_t",
                'name': "version",
                'desc': "[in] API version requested"
                })
            params.append({
                'type': "%s*"%table,
                'name': "pDdiTable",
                'desc': "[in,out] pointer to table of DDI function pointers"
                })
            export = {
                'name': "%sGet%sProcAddrTable"%(namespace, name),
                'params': params
                }

            pfn = "%s_pfnGet%sProcAddrTable_t"%(namespace, name)

            tables.append({
                'name': name, 
                'type': table,
                'export': export,
                'pfn': pfn,
                'functions': exp_objs,
                'experimental': True
            })
    return tables

"""
Public:
    returns a list of dict of each pfntables
"""
def get_zel_pfncbtables(specs, meta, namespace, tags):
    tables = []
    for cname in sorted(meta['class'], key=lambda x: meta['class'][x]['ordinal']):
        objs = get_class_function_objs(specs, cname, 1.0, 9999)
        if len(objs) > 0:
            name = get_table_name(namespace, tags, {'class': cname})
            table = "zel_%s_callbacks_t"%(_camel_to_snake(name))
            tables.append({
                'name': name, 
                'type': table,
                'functions': objs
            })
    return tables


"""
Public:
    returns a list of dict of each pfntables for all APIs introduced after 1.0
"""
def get_new_pfncbtables(specs, meta, namespace, tags):
    tables = []
    for cname in sorted(meta['class'], key=lambda x: meta['class'][x]['ordinal']):
        objs = get_class_function_objs(specs, cname, 1.1, 9999)
        if len(objs) > 0:
            name = get_table_name(namespace, tags, {'class': cname})
            table = "%s_%s_callbacks_t"%(namespace, _camel_to_snake(name))
            tables.append({
                'name': name, 
                'type': table,
                'functions': objs
            })
    return tables

"""
Public:
    returns a list of dict for converting loader input parameters
"""
def get_loader_prologue(namespace, tags, obj, meta):
    prologue = []

    params = _filter_param_list(obj['params'], ["[in]"])
    for item in params:
        if param_traits.is_mbz(item):
            continue
        if type_traits.is_class_handle(item['type'], meta):
            name = subt(namespace, tags, item['name'])
            tname = _remove_const_ptr(subt(namespace, tags, item['type']))

            # e.g., "xe_device_handle_t" -> "xe_device_object_t"
            obj_name = re.sub(r"(\w+)_handle_t", r"\1_object_t", tname)
            fty_name = re.sub(r"(\w+)_handle_t", r"\1_factory", tname)

            if type_traits.is_pointer(item['type']):
                range_start = param_traits.range_start(item)
                range_end   = param_traits.range_end(item)
                prologue.append({
                    'name': name,
                    'obj': obj_name,
                    'range': (range_start, range_end),
                    'type': tname,
                    'factory': fty_name
                })
            else:
                prologue.append({
                    'name': name,
                    'obj': obj_name,
                    'optional': param_traits.is_optional(item)
                })

    return prologue

"""
Public:
    returns a list of dict for converting loader output parameters
"""
def get_loader_epilogue(namespace, tags, obj, meta):
    epilogue = []

    for i, item in enumerate(obj['params']):
        if param_traits.is_mbz(item):
            continue
        if param_traits.is_release(item) or param_traits.is_output(item) or param_traits.is_inoutput(item):
            if type_traits.is_class_handle(item['type'], meta):
                name = subt(namespace, tags, item['name'])
                tname = _remove_const_ptr(subt(namespace, tags, item['type']))

                obj_name = re.sub(r"(\w+)_handle_t", r"\1_object_t", tname)
                fty_name = re.sub(r"(\w+)_handle_t", r"\1_factory", tname)

                if param_traits.is_range(item):
                    range_start = param_traits.range_start(item)
                    range_end   = param_traits.range_end(item)
                    epilogue.append({
                        'name': name,
                        'type': tname,
                        'obj': obj_name,
                        'factory': fty_name,
                        'release': param_traits.is_release(item),
                        'range': (range_start, range_end)
                    })
                else:
                    epilogue.append({
                        'name': name,
                        'type': tname,
                        'obj': obj_name,
                        'factory': fty_name,
                        'release': param_traits.is_release(item),
                        'optional': param_traits.is_optional(item)
                    })

    return epilogue

"""
Public:
    returns true if proc table is added after 1.0
"""
def isNewProcTable(tableName):

    return tableName in ["zesGetGlobalProcAddrTable","zesGetOverclockProcAddrTable"]