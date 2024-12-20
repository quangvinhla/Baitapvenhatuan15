#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Cấu trúc cây
struct Node {
    string title; // Tên mục
    int pageStart; // Số trang bắt đầu
    int pageEnd; // Số trang kết thúc
    vector<Node*> children;
    Node(string t, int start, int end) : title(t), pageStart(start), pageEnd(end) {}

    // tính số trang của mục
    int getPages() {
        return pageEnd - pageStart + 1;
    }
};
struct Book {
    vector<Node*> chapters; // Danh sách các chương
    // tính số chương
    int getNumberOfChapters() {
        return chapters.size();
    }
    // tìm chương dài nhất
    Node* getLongestChapter() {
        Node* longest = nullptr;
        int maxPages = 0;
        for (auto& chapter : chapters) {
            int chapterPages = chapter->getPages();
            if (chapterPages > maxPages) {
                maxPages = chapterPages;
                longest = chapter;
            }
        }
        return longest;
    }
    // Hàm tìm và xoá mục 
    bool deleteNode(Node* parent, const string& title) {
        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
            if ((*it)->title == title) {
                parent->children.erase(it);
                return true;
            }
            // Tìm kiếm trong các mục
            if (deleteNode(*it, title)) {
                return true;
            }
        }
        return false;
    }
    // Hàm tìm kiếm một mục theo tên 
    Node* searchNode(Node* parent, const string& title) {
        if (parent->title == title) {
            return parent;
        }
        // Tìm kiếm trong các mục 
        for (auto& child : parent->children) {
            Node* result = searchNode(child, title);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }
};

int main() {
    // Tạo một cuốn sách và thêm các chương
    Book book;

    // chương 1
    Node* chapter1 = new Node("Chapter 1", 1, 10);
    Node* section1 = new Node("Section 1.1", 1, 5);
    Node* subsection1 = new Node("Subsection 1.1.1", 1, 3);
    section1->children.push_back(subsection1);
    chapter1->children.push_back(section1);
    book.chapters.push_back(chapter1);

    // chương 2
    Node* chapter2 = new Node("Chapter 2", 11, 20);
    Node* section2 = new Node("Section 2.1", 11, 15);
    Node* subsection2 = new Node("Subsection 2.1.1", 11, 13);
    section2->children.push_back(subsection2);
    chapter2->children.push_back(section2);
    book.chapters.push_back(chapter2);

     // chương 3 
    Node* chapter3 = new Node("Chapter 3", 21, 50);
    Node* section3 = new Node("Section 3.1", 21, 25);
    Node* subsection3 = new Node("Subsection 3.1.1", 21, 35);
    section1->children.push_back(subsection3);
    chapter1->children.push_back(section3);
    book.chapters.push_back(chapter3);
    // Tính số chương
    cout << "Number of chapters: " << book.getNumberOfChapters() << endl;
    // Tìm chương dài nhất
    Node* longestChapter = book.getLongestChapter();
    cout << "Longest chapter is: " << longestChapter->title << " with " << longestChapter->getPages() << " pages." << endl;
    // Tìm kiếm mục "Section 2.1"
    string searchTitle = "Section 2.1";
    Node* foundNode = book.searchNode(book.chapters[1], searchTitle);
    if (foundNode) {
        cout << "Found " << searchTitle << ": " << foundNode->title
             << ", Pages: " << foundNode->pageStart << "-" << foundNode->pageEnd << endl;
    } else {
        cout << searchTitle << " not found." << endl;
    }
    // Xoá mục "Subsection 1.1.1"
    bool deleted = book.deleteNode(chapter1, "Subsection 1.1.1");
    if (deleted) {
        cout << "Subsection 1.1.1 has been deleted." << endl;
    } else {
        cout << "Subsection 1.1.1 not found." << endl;
    }
    return 0;
}