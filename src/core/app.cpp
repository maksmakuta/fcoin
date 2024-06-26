#include "app.h"
#include "logger.h"

#define ARG_SHORT "-"
#define ARG_LONG "--"

/**
 * parse args:
 *  -arg name
 *  --arg1 name
 *  --arg2=1
 * @param count
 * @param data
 */
app::app(int count ,char** data){
    str name;
    vec<str> values;
    for(u32 i = 1; i < count;i++){
        auto arg = str(data[i]);
        if(arg.starts_with(ARG_LONG)){
            if(!name.empty()){
                args[name] = values;
                values.clear();
            }
            auto d = arg.find('=');
            if(d != str::npos){
                name = arg.substr(2,d-2);
                vec<str> subvals = split(arg.substr(d+1),',');
                values.insert(values.end(),subvals.begin(), subvals.end());
                subvals.clear();
            }else{
                name = arg.substr(2);
            }
        }else if(arg.starts_with(ARG_SHORT)){
            if(!name.empty()){
                args[name] = values;
                values.clear();
            }
            name = arg.substr(1);
        }else{
            values.push_back(arg);
        }
    }
    if(!name.empty()) {
        args[name] = values;
        values.clear();
    }
}
vec<str> app::split(const str& input, char delimetr = ','){
    vec<str> result;
    strss ss(input);
    str item;
    while (getline (ss, item, delimetr)) {
        result.push_back (item);
    }
    return result;
}

vec<str> app::get(const str& key){
    if(exist(key)) {
        return args[key];
    }else{
        Log::e << "Arg " << key << " is not exist" << '\n';
        return vec<str>{};
    }
}

int app::exec(){
    return 0;
}

bool app::exist(const str& key){
    return args.contains(key);
}