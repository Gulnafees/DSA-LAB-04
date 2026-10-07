#include <iostream>
#include <string>
using namespace std;

//node structur for bit in dll
struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;

    BitNode(int val) {
        bit = val;
        next = nullptr;
        prev = nullptr;
    }
};

//class to perform binary arithmetic using dll
class BinaryDLL {
public:
    BitNode* head = nullptr;
    BitNode* tail = nullptr;

    // clear memory
    void clear() {
        BitNode* curr = head;
        while (curr != nullptr) {
            BitNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    ~BinaryDLL() {
        clear();
    }

    //append bit at tail
    void appendBit(int b) {
        BitNode* newNode = new BitNode(b);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    //prepend bit at head
    void prependBit(int b) {
        BitNode* newNode = new BitNode(b);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    //1.store binary number and pad to 8-bit block
    void storeBinary(string str) {
        clear();
        for (char c : str) {
            if (c == '0' || c == '1') {
                appendBit(c - '0');
            }
        }
        if (head == nullptr) {
            appendBit(0);
        }

        //pad to 8-bit multipel
        int len = 0;
        BitNode* curr = head;
        while (curr != nullptr) {
            len++;
            curr = curr->next;
        }

        int rem = len % 8;
        if (rem != 0) {
            int pad = 8 - rem;
            for (int i = 0; i < pad; i++) {
                prependBit(0);
            }
        }
    }

    // display binary number
    void display() {
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }
        BitNode* curr = head;
        int count = 0;
        while (curr != nullptr) {
            cout << curr->bit;
            count++;
            if (count % 8 == 0 && curr->next != nullptr) {
                cout << " ";
            }
            curr = curr->next;
        }
        cout << endl;
    }

    //helper to clone list
    BinaryDLL clone() {
        BinaryDLL copy;
        BitNode* curr = head;
        while (curr != nullptr) {
            copy.appendBit(curr->bit);
            curr = curr->next;
        }
        return copy;
    }

    //2. 1's complment
    BinaryDLL onesComplement() {
        BinaryDLL res;
        BitNode* curr = head;
        while (curr != nullptr) {
            res.appendBit(curr->bit == 0 ? 1 : 0);
            curr = curr->next;
        }
        return res;
    }

    //4. binary additon using dll
    static BinaryDLL add(BinaryDLL& num1, BinaryDLL& num2) {
        BinaryDLL result;
        BitNode* p1 = num1.tail;
        BitNode* p2 = num2.tail;
        int carry = 0;

        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1 != nullptr) {
                sum += p1->bit;
                p1 = p1->prev;
            }
            if (p2 != nullptr) {
                sum += p2->bit;
                p2 = p2->prev;
            }

            result.prependBit(sum % 2);
            carry = sum / 2;
        }

        //pad to 8-bit group
        int len = 0;
        BitNode* curr = result.head;
        while (curr != nullptr) {
            len++;
            curr = curr->next;
        }
        int rem = len % 8;
        if (rem != 0) {
            int pad = 8 - rem;
            for (int i = 0; i < pad; i++) {
                result.prependBit(0);
            }
        }

        return result;
    }

    //3. 2's complment
    BinaryDLL twosComplement() {
        BinaryDLL ones = onesComplement();
        BinaryDLL one;
        one.storeBinary("1");
        return add(ones, one);
    }

    //5. binary multplication via shift and add
    static BinaryDLL multiply(BinaryDLL& num1, BinaryDLL& num2) {
        BinaryDLL result;
        result.storeBinary("0");

        BitNode* p2 = num2.tail;
        int shift = 0;

        while (p2 != nullptr) {
            if (p2->bit == 1) {
                BinaryDLL temp = num1.clone();
                for (int i = 0; i < shift; i++) {
                    temp.appendBit(0);
                }
                result = add(result, temp);
            }
            shift++;
            p2 = p2->prev;
        }

        return result;
    }

    //6. convertion to decimel
    long long toDecimal() {
        long long dec = 0;
        BitNode* curr = head;
        while (curr != nullptr) {
            dec = (dec * 2) + curr->bit;
            curr = curr->next;
        }
        return dec;
    }
};

int main() {
    BinaryDLL bin1, bin2;
    string s1, s2;

    cout << "Enter first binary number: ";
    cin >> s1;
    bin1.storeBinary(s1);

    cout << "Binary 1 (8-bit grouped): ";
    bin1.display();

    BinaryDLL ones = bin1.onesComplement();
    cout << "1's Complement: ";
    ones.display();

    BinaryDLL twos = bin1.twosComplement();
    cout << "2's Complement: ";
    twos.display();

    cout << "Decimal Equivalent: " << bin1.toDecimal() << endl;

    cout << "\nEnter second binary number: ";
    cin >> s2;
    bin2.storeBinary(s2);

    cout << "Binary 2 (8-bit grouped): ";
    bin2.display();

    BinaryDLL sum = BinaryDLL::add(bin1, bin2);
    cout << "\nBinary Addition (bin1 + bin2): ";
    sum.display();
    cout << "Sum in Decimal: " << sum.toDecimal() << endl;

    BinaryDLL prod = BinaryDLL::multiply(bin1, bin2);
    cout << "\nBinary Multiplication (bin1 * bin2): ";
    prod.display();
    cout << "Product in Decimal: " << prod.toDecimal() << endl;

    return 0;
}