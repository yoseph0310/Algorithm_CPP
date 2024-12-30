#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Component - 폴더와 파일이 공통으로 가져야할 인터페이스
class FileSystemEntity {
protected:
    string name;
public:
    FileSystemEntity(string name) : name(name) {}
    virtual ~FileSystemEntity() {}
    
    virtual int getSize() const = 0;
    virtual void print(int indent = 0) const = 0;
};

// Leaf - 파일 클래스
class File : public FileSystemEntity {
    int size; // 파일 크기
public:
    File(string name, int size) : FileSystemEntity(name), size(size) {}

    int getSize() const override {
        return size;
    }

    void print(int indent = 0) const override {
        for (int i = 0; i < indent; ++i) cout << "\t"; // 들여쓰기
        cout << "(" << name << ", " << size << ")" << endl;
    }
};

// Composite - 폴더 클래스
class Folder : public FileSystemEntity {
    vector<FileSystemEntity*> children; // 폴더나 파일을 담을 수 있는 컨테이너
public:
    Folder(string name) : FileSystemEntity(name) {}

    ~Folder() {
        // 폴더가 제거될 때 모든 하위 파일과 폴더도 제거
        for (auto child : children) {
            delete child;
        }
    }

    void add(FileSystemEntity* entity) {
        children.push_back(entity);
    }

    int getSize() const override {
        int totalSize = 0;
        // 폴더 내 파일과 폴더의 크기 합산
        for (auto child : children) {
            totalSize += child->getSize();
        }
        return totalSize;
    }

    void print(int indent = 0) const override {
        for (int i = 0; i < indent; ++i) cout << "\t"; // 들여쓰기
        cout << "[" << name << "]" << endl;

        // 하위 파일과 폴더들 출력
        for (auto child : children) {
            child->print(indent + 1); // 더 깊이 들어갈수록 들여쓰기 증가
        }
    }
};

// main 함수
int main() {
    // 조건 1. Folder와 File의 객체를 생성할 수 있어야 함
    Folder* rootFolder = new Folder("ROOT");    // 폴더는 이름만 존재
    Folder* aaaaFolder = new Folder("AAAA");
    Folder* bbbbFolder = new Folder("BBBB");

    File* file1 = new File("a.txt", 10);        // 파일은 이름과 크기가 존재
    File* file2 = new File("b.txt", 20);
    File* file3 = new File("c.txt", 30);
    File* file4 = new File("d.txt", 40);

    // 조건 2. 폴더안에 파일 및 다른 폴더 장입 가능
    rootFolder->add(aaaaFolder);
    rootFolder->add(bbbbFolder);
    rootFolder->add(file1);

    aaaaFolder->add(file2);
    aaaaFolder->add(file3);

    bbbbFolder->add(file4);

    // 조건 3. 파일과 폴더 크기를 출력할 수 있어야 함
    cout << file1->getSize() << endl;          // 파일 크기 출력
    cout << aaaaFolder->getSize() << endl;     // 폴더 크기 출력 (내부 파일 크기 합산)
    cout << rootFolder->getSize() << endl;     // 루트 폴더 크기 출력

    // 조건 4. 화면 출력
    file1->print();         // 파일 이름과 크기만 출력
                            // ex) (a.txt, 10)

    rootFolder->print();    // ROOT 폴더 전체 모양을 보기 좋게 출력
                            // ex)
                            // [ROOT]
                            //      [AAAA]
                            //          (b.txt, 20)
                            //          (c.txt, 30)
                            //      [BBBB]
                            //          (d.txt, 40)
                            //      (a.txt, 10)

    // 조건 5. 폴더 제거시 폴더 안의 모든 파일과 폴더가 제거되어야함
    delete rootFolder;

    return 0;
}
