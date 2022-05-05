// Project UID db1f506d06d84ab787baf250c265e24e
#include <map>
#include <iostream>
#include "csvstream.h"
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <set>

using namespace std;

set<string> unique_words(const string &str) {
// Fancy modern C++ and STL way to do it
istringstream source{str};
return {istream_iterator<string>{source},
                 istream_iterator<string>{}};
}
class Classifer{
public:
    Classifer(csvstream & csvin, string debug_in){
        if(debug_in=="--debug"){
            cout<<"training data:"<<endl;
        }
        while(csvin >> row){
            ++total_num;
            num_of_label[row["tag"]]+=1;
            content_row = unique_words(row["content"]);
            if(debug_in=="--debug"){
                cout<<"  label = "<< row["tag"]<<", content = "<<row["content"]<<endl;
            }
            for (auto &word : content_row){
                auto key = word;
                num_of_unique_words[key]+=1;
                num_of_posts_given_label[row["tag"]][key]+=1;
            }
        }
        num_of_unique_word = num_of_unique_words.size();
}
    void print_debug(){
        cout<<"trained on "<<total_num<<" examples"<<endl;
        cout<<"vocabulary size = "<<num_of_unique_word<<endl<<endl;
        cout<<"classes:"<<endl;
        for (auto &word : num_of_label){
        auto label = word.first;
            log_prior = log(static_cast<double>(num_of_label[label])
                            /static_cast<double>(total_num));
            cout<<"  "<<label<<", "<<num_of_label[label];
            cout<<" examples, log-prior = "<<log_prior<<endl;
        }
      cout<<"classifier parameters:"<<endl;
      for (auto &pair : num_of_posts_given_label){
          auto temp = pair.first;
          auto time = pair.second;
          for(auto &word: time){
              auto tag = word.first;
              auto cont = word.second;
              cout<<"  "<<temp<<":"<<tag<<", count = "<<cont<<", log-likelihood = ";
              cout<<log(static_cast<double>(cont)
                        /static_cast<double>(num_of_label[temp]))<<endl;
          }
      }
    }
    void print_line(){
        cout<<"trained on "<<total_num<<" examples"<<endl;
    }
   
    void test(csvstream & csvin_test){
    double sum = 0;
    cout<<"test data:"<<endl;
    while (csvin_test >> row_test) {
        ++num_total;
      set<string> uw = unique_words(row_test["content"]);
      for (auto &word : num_of_label){
        auto label_test = word.first;
        for (auto &word : uw){
          auto key = word;
          if(num_of_unique_words.find(key)==num_of_unique_words.end()){
            sum+=log(static_cast<double>(1)/static_cast<double>(total_num));
          }
          else if(num_of_posts_given_label[label_test].find(key)
                  !=num_of_posts_given_label[label_test].end()){
            sum+=log(static_cast<double>(num_of_posts_given_label[label_test][key])
                     /static_cast<double>(num_of_label[label_test]));
           }
          else if(num_of_posts_given_label[label_test].find(key)
                  ==num_of_posts_given_label[label_test].end()){
              sum+=log(static_cast<double>(num_of_unique_words[key])
                       /static_cast<double>(total_num));
           }
        }
          sum+=log(static_cast<double>(num_of_label[label_test])
                   /static_cast<double>(total_num));
          log_score_of_c[label_test] = sum;
          sum = 0;
      }
               pair<string, double> max_mem;
               max(max_mem);
               cout<<"  correct = "<<row_test["tag"]<<", predicted = ";
               cout<<max_mem.first<<", log-probability score = "<< max_mem.second <<endl;
               if(row_test["tag"]==max_mem.first){
                   ++num_of_correct;
        }
        cout<<"  content = "<<row_test["content"]<<endl<<endl;
    }
        cout<<"performance: "<<num_of_correct<<" / "<<num_total;
        cout<<" posts predicted correctly"<<endl;
 }
    void max(pair<string, double> & max_member){
        max_member.first = "";
        max_member.second = log_score_of_c.begin()->second;
        for (auto &word : log_score_of_c){
            if(max_member.second<=word.second){
            max_member.second = word.second;
            max_member.first = word.first;
            }
        }
    }
  
private:
    int total_num = 0;
    size_t num_of_unique_word = 0;
    map<string, int> num_of_unique_words;
    map<string, int> num_of_posts;
    map<string, int> num_of_label;
    map<string, map<string,int>>num_of_posts_given_label;
    set<string> content;
    set<string> label;
    map<string, double> log_score_of_c;
    map<string, string> chosen_tag;
    double log_prior = 0;
    map<string, string> row;
    map<string, string> row_test;
    set<string> content_row;
    int num_total = 0;
    int num_of_correct = 0;
};

int main(int argc, char * argv[]) {
    cout.precision(3);
    string de = "--debug";
    string debug = "";
    if (argc!=3) {
        if(argc!=4){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
        }
        else if(argv[3]!= de){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
        }
        else{
            debug = argv[3];
        }
    }
    ifstream pack_in(argv[1]);
    ifstream pack_out(argv[2]);
    string filename = argv[1];
    string testname = argv[2];
    if (!pack_in.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return -1;
    }
    if(!pack_out.is_open()){
        cout << "Error opening file: " << testname << endl;
        return -1;
    }
    csvstream csvin(filename);
    csvstream csvin_test(testname);
    Classifer classifer(csvin, debug);
    if(argc==3){
        classifer.print_line();
        classifer.test(csvin_test);
    }
    else if(argv[3] == de){
        classifer.print_debug();
        classifer.test(csvin_test);
    }
}



    //     for(auto &col:row){
    //     const string &column_name = col.first;
    //     const string &datum = col.second;
    //     cout<<" "<<column_name<<": "<<datum<<"\n";
