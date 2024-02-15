#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <ctype.h>
#include "./pugixml-1.14/src/pugixml.hpp"

using namespace std;
using namespace pugi;

double evaluatePrefix(string prefixExp)
{

    stack<double> operendStack;
    int size = prefixExp.size() - 1;

    for (int i = size; i >= 0; i--)
    {
        string tp = "";
        while(prefixExp[i] != ' ' && i >= 0){
            tp += prefixExp[i];
            i--;
        }
        if(tp.length()>1)reverse(tp.begin(),tp.end());
        if (tp!="+" && tp!="-" && tp!="*" && tp!="/"){
            double x = stod(tp);
            operendStack.push(x);
        }
        else
        {
            double o1 = operendStack.top();
            operendStack.pop();
            double o2 = operendStack.top();
            operendStack.pop();
            if (tp == "+")
                operendStack.push(o1 + o2);
            else if (tp == "-")
                operendStack.push(o1 - o2);
            else if (tp == "*")
                operendStack.push(o1 * o2);
            else if (tp == "/")
                operendStack.push(o1 / o2);
            else
            {
                cout << "Invalid Expression";
                return -1;
            }
        }
    }
    return operendStack.top();
}

pair<double,double> getVal(string file_name){
    xml_document doc;
    if (!doc.load_file(file_name.c_str())) {
        cout << "Failed to load XML file." << endl;
        return {-1,-1};
    }

    xml_node root = doc.child("Kingdom");
    if (!root) {
        cout << "Root node not found." << endl;
        return {-1,-1};
    }

    xml_node tot_W = root.child("KingdomWealth");
    xml_node min_W = root.child("MinimumClanWealth");
    if (!tot_W || !min_W) {
        cout << "Child node not found." << endl;
        return {-1,-1};
    }
    return {stod(tot_W.child_value()),stod(min_W.child_value())};
    

}

void getClanWealth(string file_name, vector<pair<string,double>> &clandetails){
    xml_document doc;
    if (!doc.load_file(file_name.c_str())) {
        cout << "Failed to load XML file." << endl;
        return;
    }

    xml_node root = doc.child("Kingdom");
    if (!root) {
        cout << "Root node not found." << endl;
        return;
    }

    for (xml_node clan = root.child("Clan"); clan; clan = clan.next_sibling("Clan")) {
        clandetails.push_back({clan.child_value("Name"),evaluatePrefix(clan.child_value("Wealth"))});
    }

}





int main() {
    vector<pair<string,double>> clandetails;
    pair<double,double> wealth = getVal("sample.xml");
    double tot_W = wealth.first;
    double min_W = wealth.second;
    getClanWealth("sample.xml",clandetails);
    for(auto x:clandetails){
        cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;

   
}