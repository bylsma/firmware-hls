--! Standard libraries
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--! User packages
use work.tf_pkg.all;

package memUtil_pkg is

  -- ########################### Types ###########################

  type enum_AS_36 is (L1PHIDn3,L2PHIBn5,L2PHICn2);

  type enum_VMSTE_22 is (L1PHID14n4,L1PHID14n5,L1PHID15n1,L1PHID15n2,L1PHID15n3,L1PHID15n4,L1PHID15n5,L1PHID16n1,L1PHID16n2,L1PHID16n3,L1PHID16n4,L1PHID16n5);

  type enum_VMSTE_16 is (L2PHIB13n5,L2PHIB14n4,L2PHIB14n5,L2PHIB15n2,L2PHIB15n3,L2PHIB15n4,L2PHIB16n1,L2PHIB16n2,L2PHIB16n3,L2PHIC17n1,L2PHIC17n2,L2PHIC18n1);

  type enum_SP_14 is (L1PHID14_L2PHIB15,L1PHID14_L2PHIB16,L1PHID15_L2PHIB13,L1PHID15_L2PHIB14,L1PHID15_L2PHIB15,L1PHID15_L2PHIB16,L1PHID15_L2PHIC17,L1PHID16_L2PHIB14,L1PHID16_L2PHIB15,L1PHID16_L2PHIB16,L1PHID16_L2PHIC17,L1PHID16_L2PHIC18);

  type enum_TPROJ_60 is (L1L2F_L3PHIB,L1L2F_L3PHIC);

  type enum_TPROJ_58 is (L1L2F_L4PHIB,L1L2F_L4PHIC,L1L2F_L5PHIB,L1L2F_L5PHIC,L1L2F_L6PHIA,L1L2F_L6PHIB,L1L2F_L6PHIC);

  type enum_TPROJ_59 is (L1L2F_D1PHIA,L1L2F_D1PHIB,L1L2F_D1PHIC,L1L2F_D1PHID,L1L2F_D2PHIA,L1L2F_D2PHIB,L1L2F_D2PHIC,L1L2F_D3PHIA,L1L2F_D3PHIB,L1L2F_D3PHIC,L1L2F_D4PHIA,L1L2F_D4PHIB,L1L2F_D4PHIC);

  type enum_TPAR_70 is (L1L2F);

  type t_arr_AS_36_1b is array(enum_AS_36) of std_logic;
  type t_arr_AS_36_ADDR is array(enum_AS_36) of std_logic_vector(9 downto 0);
  type t_arr_AS_36_DATA is array(enum_AS_36) of std_logic_vector(35 downto 0);
  type t_arr_AS_36_NENT is array(enum_AS_36) of t_arr8_7b;
  type t_arr_VMSTE_22_1b is array(enum_VMSTE_22) of std_logic;
  type t_arr_VMSTE_22_ADDR is array(enum_VMSTE_22) of std_logic_vector(7 downto 0);
  type t_arr_VMSTE_22_DATA is array(enum_VMSTE_22) of std_logic_vector(21 downto 0);
  type t_arr_VMSTE_22_NENT is array(enum_VMSTE_22) of t_arr2_7b;
  type t_arr_VMSTE_16_1b is array(enum_VMSTE_16) of std_logic;
  type t_arr_VMSTE_16_ADDR is array(enum_VMSTE_16) of std_logic_vector(7 downto 0);
  type t_arr_VMSTE_16_DATA is array(enum_VMSTE_16) of std_logic_vector(15 downto 0);
  type t_arr_VMSTE_16_NENT is array(enum_VMSTE_16) of t_arr2_8_5b;
  type t_arr_SP_14_1b is array(enum_SP_14) of std_logic;
  type t_arr_SP_14_ADDR is array(enum_SP_14) of std_logic_vector(7 downto 0);
  type t_arr_SP_14_DATA is array(enum_SP_14) of std_logic_vector(13 downto 0);
  type t_arr_SP_14_NENT is array(enum_SP_14) of t_arr2_7b;
  type t_arr_TPROJ_60_1b is array(enum_TPROJ_60) of std_logic;
  type t_arr_TPROJ_60_ADDR is array(enum_TPROJ_60) of std_logic_vector(7 downto 0);
  type t_arr_TPROJ_60_DATA is array(enum_TPROJ_60) of std_logic_vector(59 downto 0);
  type t_arr_TPROJ_60_NENT is array(enum_TPROJ_60) of t_arr2_7b;
  type t_arr_TPROJ_58_1b is array(enum_TPROJ_58) of std_logic;
  type t_arr_TPROJ_58_ADDR is array(enum_TPROJ_58) of std_logic_vector(7 downto 0);
  type t_arr_TPROJ_58_DATA is array(enum_TPROJ_58) of std_logic_vector(57 downto 0);
  type t_arr_TPROJ_58_NENT is array(enum_TPROJ_58) of t_arr2_7b;
  type t_arr_TPROJ_59_1b is array(enum_TPROJ_59) of std_logic;
  type t_arr_TPROJ_59_ADDR is array(enum_TPROJ_59) of std_logic_vector(7 downto 0);
  type t_arr_TPROJ_59_DATA is array(enum_TPROJ_59) of std_logic_vector(58 downto 0);
  type t_arr_TPROJ_59_NENT is array(enum_TPROJ_59) of t_arr2_7b;
  type t_arr_TPAR_70_1b is array(enum_TPAR_70) of std_logic;
  type t_arr_TPAR_70_ADDR is array(enum_TPAR_70) of std_logic_vector(9 downto 0);
  type t_arr_TPAR_70_DATA is array(enum_TPAR_70) of std_logic_vector(69 downto 0);
  type t_arr_TPAR_70_NENT is array(enum_TPAR_70) of t_arr8_7b;

  -- ########################### Functions ###########################

  -- Following functions are needed because VHDL doesn't preserve case when converting an enum to a string using image
  function memory_enum_to_string(val: enum_AS_36) return string;
  function memory_enum_to_string(val: enum_VMSTE_22) return string;
  function memory_enum_to_string(val: enum_VMSTE_16) return string;
  function memory_enum_to_string(val: enum_SP_14) return string;
  function memory_enum_to_string(val: enum_TPROJ_60) return string;
  function memory_enum_to_string(val: enum_TPROJ_58) return string;
  function memory_enum_to_string(val: enum_TPROJ_59) return string;
  function memory_enum_to_string(val: enum_TPAR_70) return string;

end package memUtil_pkg;

package body memUtil_pkg is

  -- ########################### Functions ###########################

  function memory_enum_to_string(val: enum_AS_36) return string is
  begin
    case val is
       when L1PHIDn3 => return "L1PHIDn3";
       when L2PHIBn5 => return "L2PHIBn5";
       when L2PHICn2 => return "L2PHICn2";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_VMSTE_22) return string is
  begin
    case val is
       when L1PHID14n4 => return "L1PHID14n4";
       when L1PHID14n5 => return "L1PHID14n5";
       when L1PHID15n1 => return "L1PHID15n1";
       when L1PHID15n2 => return "L1PHID15n2";
       when L1PHID15n3 => return "L1PHID15n3";
       when L1PHID15n4 => return "L1PHID15n4";
       when L1PHID15n5 => return "L1PHID15n5";
       when L1PHID16n1 => return "L1PHID16n1";
       when L1PHID16n2 => return "L1PHID16n2";
       when L1PHID16n3 => return "L1PHID16n3";
       when L1PHID16n4 => return "L1PHID16n4";
       when L1PHID16n5 => return "L1PHID16n5";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_VMSTE_16) return string is
  begin
    case val is
       when L2PHIB13n5 => return "L2PHIB13n5";
       when L2PHIB14n4 => return "L2PHIB14n4";
       when L2PHIB14n5 => return "L2PHIB14n5";
       when L2PHIB15n2 => return "L2PHIB15n2";
       when L2PHIB15n3 => return "L2PHIB15n3";
       when L2PHIB15n4 => return "L2PHIB15n4";
       when L2PHIB16n1 => return "L2PHIB16n1";
       when L2PHIB16n2 => return "L2PHIB16n2";
       when L2PHIB16n3 => return "L2PHIB16n3";
       when L2PHIC17n1 => return "L2PHIC17n1";
       when L2PHIC17n2 => return "L2PHIC17n2";
       when L2PHIC18n1 => return "L2PHIC18n1";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_SP_14) return string is
  begin
    case val is
       when L1PHID14_L2PHIB15 => return "L1PHID14_L2PHIB15";
       when L1PHID14_L2PHIB16 => return "L1PHID14_L2PHIB16";
       when L1PHID15_L2PHIB13 => return "L1PHID15_L2PHIB13";
       when L1PHID15_L2PHIB14 => return "L1PHID15_L2PHIB14";
       when L1PHID15_L2PHIB15 => return "L1PHID15_L2PHIB15";
       when L1PHID15_L2PHIB16 => return "L1PHID15_L2PHIB16";
       when L1PHID15_L2PHIC17 => return "L1PHID15_L2PHIC17";
       when L1PHID16_L2PHIB14 => return "L1PHID16_L2PHIB14";
       when L1PHID16_L2PHIB15 => return "L1PHID16_L2PHIB15";
       when L1PHID16_L2PHIB16 => return "L1PHID16_L2PHIB16";
       when L1PHID16_L2PHIC17 => return "L1PHID16_L2PHIC17";
       when L1PHID16_L2PHIC18 => return "L1PHID16_L2PHIC18";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_TPROJ_60) return string is
  begin
    case val is
       when L1L2F_L3PHIB => return "L1L2F_L3PHIB";
       when L1L2F_L3PHIC => return "L1L2F_L3PHIC";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_TPROJ_58) return string is
  begin
    case val is
       when L1L2F_L4PHIB => return "L1L2F_L4PHIB";
       when L1L2F_L4PHIC => return "L1L2F_L4PHIC";
       when L1L2F_L5PHIB => return "L1L2F_L5PHIB";
       when L1L2F_L5PHIC => return "L1L2F_L5PHIC";
       when L1L2F_L6PHIA => return "L1L2F_L6PHIA";
       when L1L2F_L6PHIB => return "L1L2F_L6PHIB";
       when L1L2F_L6PHIC => return "L1L2F_L6PHIC";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_TPROJ_59) return string is
  begin
    case val is
       when L1L2F_D1PHIA => return "L1L2F_D1PHIA";
       when L1L2F_D1PHIB => return "L1L2F_D1PHIB";
       when L1L2F_D1PHIC => return "L1L2F_D1PHIC";
       when L1L2F_D1PHID => return "L1L2F_D1PHID";
       when L1L2F_D2PHIA => return "L1L2F_D2PHIA";
       when L1L2F_D2PHIB => return "L1L2F_D2PHIB";
       when L1L2F_D2PHIC => return "L1L2F_D2PHIC";
       when L1L2F_D3PHIA => return "L1L2F_D3PHIA";
       when L1L2F_D3PHIB => return "L1L2F_D3PHIB";
       when L1L2F_D3PHIC => return "L1L2F_D3PHIC";
       when L1L2F_D4PHIA => return "L1L2F_D4PHIA";
       when L1L2F_D4PHIB => return "L1L2F_D4PHIB";
       when L1L2F_D4PHIC => return "L1L2F_D4PHIC";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

  function memory_enum_to_string(val: enum_TPAR_70) return string is
  begin
    case val is
       when L1L2F => return "L1L2F";
    end case;
    return "No conversion found.";
  end memory_enum_to_string;

end package body memUtil_pkg;
