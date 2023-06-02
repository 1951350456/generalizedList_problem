#include <bits/stdc++.h>

using namespace std;
struct Postgraduate{
    string name;
    vector<string> undergraduates;
};
class GeneralizedList {
public:
    string data;
    //根据老师查询学生
    unordered_map<string, vector<string>> table;
    //根据老师查询研究生
    unordered_map<string, vector<string>> table1;
    //根据研究生查询学生
    unordered_map<string, vector<string>> table2;
    int teachers_num=0;
    int students_num=0;
    int postgraduates_num=0;
    void insert(const string& teacher, const vector<string>& students) {
        data += "(" + teacher + ", (";
        for (int i = 0; i < students.size(); i++) {
            data += students[i];
            if (i < students.size() - 1) {
                data += ", ";
            }
            students_num++;
        }
        data += "))";
        table[teacher] = students;
        teachers_num++;
    }
    void insert(const string& teacher, const vector<Postgraduate>& postgraduates) {
        data += "(" + teacher + ", (";
        for (int i = 0; i < postgraduates.size(); i++){
            data += postgraduates[i].name + ", (";
            for(int j = 0; j < postgraduates[i].undergraduates.size(); j++){
                data += postgraduates[i].undergraduates[j];
                if (j < postgraduates[i].undergraduates.size() - 1) {
                    data += ", ";
                }
                students_num++;
            }
            postgraduates_num++;
            data += ")";
            table2[postgraduates[i].name] = postgraduates[i].undergraduates;
            if (i < postgraduates.size() - 1) {
                data += ", ";
            }
        }
        data += "))";
        vector<string> u;
        for(int i = 0; i < postgraduates.size(); i++){
            u.push_back(postgraduates[i].name);
        }
        table1[teacher] = u;
        teachers_num++;
    }

    void remove(const string& person) {
        int pos = data.find("(" + person + ",");
        if (pos != string::npos) {
            int start = pos;
            int end = start;
            int count = 0;
            while (end < data.length()) {
                if (data[end] == '(') {
                    count++;
                } else if (data[end] == ')') {
                    count--;
                }
                if (count == 0) {
                    break;
                }
                end++;
            }
            data = data.substr(0, start) + data.substr(end + 1);
            table.erase(person);
            table1.erase(person);
            table2.erase(person);
        }
    }

    vector<string> query(const string& person) const {
        if (table.count(person) > 0) {
            return table.at(person);
        }
        else if (table2.count(person) > 0) {
            return table2.at(person);
        }
        else if(table1.count(person) > 0) {
            return table1.at(person);
        }
        else {
            return {};
        }
    }

    void print() const {
        cout << data << endl;
    }
};

int main() {
    GeneralizedList list;
    list.insert("teacher1", {"student1", "student2", "student3"});
    Postgraduate a = {"postgraduate1",{"student4", "student5", "student6"}};
    Postgraduate b = {"postgraduate2",{"student7","student8","student9"}};
    vector<Postgraduate> m = {a,b};
    list.insert("teacher2", m);
    list.insert("teacher3", {"student6"});
    list.print();
    vector<string> student = list.query("teacher2");
    cout << "teacher2's students: ";
    for(int i = 0;i<student.size();i++){
        cout<<student[i]<<" ";
    }
    cout<<endl;
    list.remove("teacher2");
    list.print();
    vector<string> students = list.query("teacher1");
    cout << "teacher1's students: ";
    for (int i = 0; i < students.size(); i++) {
        cout << students[i] << " ";
    }
    cout << endl;
    students = list.query("teacher2");
    cout << "teacher2's students: ";
    for (int i = 0; i < students.size(); i++) {
        cout << students[i] << " ";
    }
    cout << endl;
    return 0;
}