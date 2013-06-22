#ifndef CHOICES_145313413_H
#define CHOICES_145313413_H

namespace choices {

  typedef std::map<std::string, std::string> options;

  std::ostream& operator<<(std::ostream& stm, const options& opt)
  {
    options::const_iterator it;
    stm << "{ ";
    for(it = opt.begin(); it != opt.end(); it++)
    {
      stm << (*it).first << ": " << (*it).second << " ";
    }

    stm << "}" << std::endl;

    return stm;
  }

  namespace details {
    void as_vect(int argc, const char *argv[], std::vector<std::string>& res)
    {
      res.assign(argv, argv + argc);
    }

    std::string removePrefix(const std::string s)
    {
      size_t pos = s.find("--");
      return pos == std::string::npos ? s : s.substr(pos + 2);
    }

    void as_map(std::vector<std::string> v, options& o)
    {
      for(size_t i=0; i<v.size(); i++)
      {
        o[v[i]] = "";
      }
    }
  }

  namespace d = details;

  options parse_cmd(int argc, const char *argv[])
  {
    std::vector<std::string> v;
    d::as_vect(argc, argv, v);

    v.erase(v.begin());

    std::vector<std::string> v2(v.size());
    std::transform(v.begin(), v.end(), v2.begin(), d::removePrefix);

    options o;
    d::as_map(v2, o);

    return o;
  }

  bool has_option(const std::string& option, const options& opt)
  {
    return opt.find(option) != opt.end();
  }
}

#endif
