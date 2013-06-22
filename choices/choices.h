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

    std::string remove_prefix(const std::string s)
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
    
    bool is_flag(const std::string& s)
    {
      return s.find("--") == 0;
    }

    bool is_value(const std::string& s)
    {
      return !is_flag(s);
    }

    bool has_flag(const std::pair<std::string, std::string> p)
    {
      return p.first != "";
    }

    void clear(std::pair<std::string, std::string> p)
    {
      p.first = p.second = "";
    }

    void get_options(const std::vector<std::string> v, options& opt)
    {
      std::pair<std::string, std::string> curr;

      std::vector<std::string>::const_iterator it;
      for(it = v.begin(); it != v.end(); it++)
      {
        if(is_flag(*it))
        {
          if(has_flag(curr))
          {
            opt.insert(curr);
            clear(curr);
          }

          curr.first = remove_prefix(*it);
        }
        else
        {
          if(has_flag(curr))
          {
            curr.second = *it;
            opt.insert(curr);
            clear(curr);
          }
        }
      }

      if(has_flag(curr))
      {
        opt.insert(curr);
        clear(curr);
      }
    }

  }

  namespace d = details;

  options parse_cmd(int argc, const char *argv[])
  {
    std::vector<std::string> v;
    d::as_vect(argc, argv, v);

    v.erase(v.begin());

    options o;
    d::get_options(v, o);

    return o;
  }

  bool has_option(const std::string& option, const options& opt)
  {
    return opt.find(option) != opt.end();
  }

  const std::string& option_value(const std::string& option, const options& opt)
  {
    options::const_iterator it = opt.find(option);
    return (*it).second;
  }
}

#endif
