#include<iostream>
#include<vector>
#include<string>


using namespace std;

class DocumentEditor{
    private:
    vector<string>elements; //this will contain the whole eleents of current document
    string renderdocument; //this will contain the whole previously saved document;
    
    public:
    void addText(string text){
        elements.push_back(text);
    };

    void addImage(string path){
        elements.push_back(path);
    };

    //this will show th whole doucment data
    void renderedDocument(){
        //if data is present in render document or not
        if(renderdocument.empty()){
            string result;

            for(auto & elems : elements){
                
                //check is the element is image path
                if(elems.substr('.jpg')){
                    result += 
                }
            }
        }
    }

    void saveDocument(){

    }
};

int main(){
    cout<<"Hello word"<<endl;
    return 0;
}