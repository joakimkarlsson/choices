#include <igloo/igloo_alt.h>
using namespace igloo;

#include <choices/choices.h>
namespace c = choices;

Describe(a_parser)
{
  It(contains_no_options_if_no_arguments_are_specified) 
  {
    int argc = 1;
    const char *argv[] = {"path/to/executable"};
    c::options options = c::parse_cmd(argc, argv);
    AssertThat(options, Is().Empty());
  }

  It(returns_flags_as_empty_strings)
  {
    int argc = 2;
    const char *argv[] = {"path/to/executable", "--version"};
    c::options options = c::parse_cmd(argc, argv);
    AssertThat(options, Is().OfLength(1));
  }

  It(tells_when_a_flag_isnt_present)
  {
    int argc = 2;
    const char *argv[] = {"path/to/executable", "--version"};
    c::options options = c::parse_cmd(argc, argv);

    AssertThat(c::has_option("not_there", options), Is().False());
  }

  It(tells_when_a_flag_is_present)
  {
    int argc = 2;
    const char *argv[] = {"path/to/executable", "--version"};
    c::options options = c::parse_cmd(argc, argv);

    AssertThat(c::has_option("version", options), Is().True());
  }

  It(reads_options_with_values)
  {
    int argc = 2;
    const char *argv[] = {"path/to/executable", "--option=value"};
    c::options options = c::parse_cmd(argc, argv);

    AssertThat(c::has_option("option", options), Is().True());
    AssertThat(c::option_value("option", options), Is().EqualTo("value"));
  }

};
