#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char maSV[10];
    int maLop;
    char tenSV[255];
    float diemToan, diemLy, diemHoa;
} SinhVien;
typedef struct {
    int maLop;
    char tenLop[10];
    int khoa;
} Lop;

typedef struct Node {
    SinhVien sinhVien;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(SinhVien sv) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->sinhVien = sv;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertSinhVien(Node* root, SinhVien sv) {
    if (root == NULL) {
        return createNode(sv);
    }

    int compareResult = strcmp(sv.maSV, root->sinhVien.maSV);
    if (compareResult < 0) {
        root->left = insertSinhVien(root->left, sv);
    } else if (compareResult > 0) {
        root->right = insertSinhVien(root->right, sv);
    } else {
        printf("Sinh vien da ton tai trong danh sach.\n");
    }

    return root;
}

void themLop(Lop danhSachLop[], int* soLuongLop) {
    if (*soLuongLop >= 10) {
        printf("Danh sach lop da day. Khong the them lop moi.\n");
        return;
    }

    Lop lopMoi;
    printf("Nhap ma lop: ");
    scanf("%d", &lopMoi.maLop);

    printf("Nhap ten lop: ");
    scanf("%s", lopMoi.tenLop);

    printf("Nhap khoa: ");
    scanf("%d", &lopMoi.khoa);

    danhSachLop[*soLuongLop] = lopMoi;
    (*soLuongLop)++;
}

void themSinhVien(Node** rootPtr, Lop danhSachLop[], int soLuongLop) {
    if (soLuongLop == 0) {
        printf("Chua co lop nao trong danh sach. Vui long them lop truoc.\n");
        return;
    }

    SinhVien svMoi;
    printf("Nhap ma sinh vien: ");
    scanf("%s", svMoi.maSV);

    printf("Nhap ma lop: ");
    scanf("%d", &svMoi.maLop);

    // Ki?m tra m� l?p c� t?n t?i trong danh s�ch l?p hay kh�ng
    int i;
    for (i = 0; i < soLuongLop; i++) {
        if (danhSachLop[i].maLop == svMoi.maLop) {
            break;
        }
    }

    if (i == soLuongLop) {
        printf("Ma lop khong ton tai trong danh sach.\n");
        return;
    }

    printf("Nhap ten sinh vien: ");
    scanf(" %[^\n]", svMoi.tenSV);

    printf("Nhap diem Toan: ");
    scanf("%f", &svMoi.diemToan);

    printf("Nhap diem Ly: ");
    scanf("%f", &svMoi.diemLy);

    printf("Nhap diem Hoa: ");
    scanf("%f", &svMoi.diemHoa);

    *rootPtr = insertSinhVien(*rootPtr, svMoi);
    printf("Them sinh vien thanh cong.\n");
}
Node* searchSinhVien(Node* root, char maSV[]) {
    if (root == NULL) {
        return NULL; // Kh�ng t�m th?y sinh vi�n
    }

    int compareResult = strcmp(maSV, root->sinhVien.maSV);
    if (compareResult < 0) {
        return searchSinhVien(root->left, maSV);
    } else if (compareResult > 0) {
        return searchSinhVien(root->right, maSV);
    } else {
        return root; // T�m th?y sinh vi�n
    }
}

void hienThiThongTinSinhVien(Node* svNode, Lop danhSachLop[], int soLuongLop) {
    if (svNode == NULL) {
        printf("Khong tim thay sinh vien.\n");
        return;
    }

    SinhVien sv = svNode->sinhVien;
    printf("Thong tin sinh vien:\n");
    printf("Ma SV: %s\n", sv.maSV);
    printf("Ten SV: %s\n", sv.tenSV);
    printf("Diem Toan: %.2f\n", sv.diemToan);
    printf("Diem Ly: %.2f\n", sv.diemLy);
    printf("Diem Hoa: %.2f\n", sv.diemHoa);
    
    // T�m th�ng tin l?p c?a sinh vi�n
    int i;
    for (i = 0; i < soLuongLop; i++) {
        if (danhSachLop[i].maLop == sv.maLop) {
            printf("Ma Lop: %d\n", sv.maLop);
            printf("Ten Lop: %s\n", danhSachLop[i].tenLop);
            break;
        }
    }
}
void ghiSinhVien(FILE* file, SinhVien sv) {
    fprintf(file, "%s %d %s %.2f %.2f %.2f\n", sv.maSV, sv.maLop, sv.tenSV, sv.diemToan, sv.diemLy, sv.diemHoa);
}

// Ghi th�ng tin m?t l?p v�o file
void ghiLop(FILE* file, Lop lop) {
    fprintf(file, "%d %s %d\n", lop.maLop, lop.tenLop, lop.khoa);
}

// H�m ghi to�n b? c�y nh? ph�n t�m ki?m (danh s�ch sinh vi�n) v�o file
void ghiDanhSachSinhVien(FILE* file, Node* root) {
    if (root != NULL) {
        ghiDanhSachSinhVien(file, root->left);
        ghiSinhVien(file, root->sinhVien);
        ghiDanhSachSinhVien(file, root->right);
    }
}

// H�m ghi danh s�ch l?p v�o file
void ghiDanhSachLop(FILE* file, Lop danhSachLop[], int soLuongLop) {
    for (int i = 0; i < soLuongLop; i++) {
        ghiLop(file, danhSachLop[i]);
    }
}
// H�m hi?n th? th�ng tin c?a m?t sinh vi�n
void hienThiThongTinMotSinhVien(SinhVien sv) {
    printf("Ma SV: %s\n", sv.maSV);
    printf("Ten SV: %s\n", sv.tenSV);
    printf("Diem Toan: %.2f\n", sv.diemToan);
    printf("Diem Ly: %.2f\n", sv.diemLy);
    printf("Diem Hoa: %.2f\n", sv.diemHoa);
    printf("Diem Trung Binh: %.2f\n", (sv.diemToan + sv.diemLy + sv.diemHoa) / 3.0);
}

// H�m hi?n th? danh s�ch sinh vi�n theo m� sinh vi�n tang d?n
void hienThiDanhSachSinhVienTheoMaSV(Node* root) {
    if (root != NULL) {
        hienThiDanhSachSinhVienTheoMaSV(root->left);
        hienThiThongTinMotSinhVien(root->sinhVien);
        printf("\n");
        hienThiDanhSachSinhVienTheoMaSV(root->right);
    }
}

// H�m ki?m tra t�n sinh vi�n c� kh?p v?i t�n c?n t�m hay kh�ng
// N?u c� kh?p, h�m s? hi?n th? th�ng tin sinh vi�n v� tr? v? 1, ngu?c l?i tr? v? 0
int timSinhVienTheoTen(Node* root, char tenSV[]) {
    if (root == NULL) {
        return 0;
    }

    int compareResult = strcmp(tenSV, root->sinhVien.tenSV);
    if (compareResult < 0) {
        return timSinhVienTheoTen(root->left, tenSV);
    } else if (compareResult > 0) {
        return timSinhVienTheoTen(root->right, tenSV);
    } else {
        hienThiThongTinMotSinhVien(root->sinhVien);
        return 1;
    }
}

// H�m t�m v� hi?n th? t?t c? sinh vi�n theo t�n
int timVaHienThiTatCaSinhVienTheoTen(Node* root, char tenSV[]) {
    int found = 0;
    if (root != NULL) {
        found = timSinhVienTheoTen(root, tenSV) || found;
        found = timVaHienThiTatCaSinhVienTheoTen(root->left, tenSV) || found;
        found = timVaHienThiTatCaSinhVienTheoTen(root->right, tenSV) || found;
    }

    return found;
}

// H�m ki?m tra m� l?p c?a sinh vi�n c� kh?p v?i m� l?p c?n t�m hay kh�ng
// N?u c� kh?p, h�m s? hi?n th? th�ng tin sinh vi�n v� tr? v? 1, ngu?c l?i tr? v? 0
int timSinhVienTheoMaLop(Node* root, int maLop) {
    if (root == NULL) {
        return 0;
    }

    if (maLop < root->sinhVien.maLop) {
        return timSinhVienTheoMaLop(root->left, maLop);
    } else if (maLop > root->sinhVien.maLop) {
        return timSinhVienTheoMaLop(root->right, maLop);
    } else {
        hienThiThongTinMotSinhVien(root->sinhVien);
        return 1;
    }
}

// H�m t�m Node ch?a th�ng tin sinh vi�n c� m� SV c?n x�a
Node* timNodeSinhVienTheoMaSV(Node* root, char maSV[]) {
    if (root == NULL || strcmp(maSV, root->sinhVien.maSV) == 0) {
        return root;
    }

    if (strcmp(maSV, root->sinhVien.maSV) < 0) {
        return timNodeSinhVienTheoMaSV(root->left, maSV);
    } else {
        return timNodeSinhVienTheoMaSV(root->right, maSV);
    }
}

// H�m t�m node th? m?ng (node l?n nh?t trong c�y con tr�i) c?a node c?n x�a
Node* timNodeTheMang(Node* root) {
    Node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

// H�m x�a m?t sinh vi�n ra kh?i danh s�ch
Node* xoaSinhVien(Node* root, char maSV[]) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(maSV, root->sinhVien.maSV) < 0) {
        root->left = xoaSinhVien(root->left, maSV);
    } else if (strcmp(maSV, root->sinhVien.maSV) > 0) {
        root->right = xoaSinhVien(root->right, maSV);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* theMang = timNodeTheMang(root->left);

        // Copy the inorder successor's content to this node
        root->sinhVien = theMang->sinhVien;

        // Delete the inorder successor
        root->left = xoaSinhVien(root->left, theMang->sinhVien.maSV);
    }
    return root;
}
// H�m t�m v� hi?n th? t?t c? sinh vi�n theo m� l?p
int timVaHienThiTatCaSinhVienTheoMaLop(Node* root, int maLop) {
    int found = 0;
    if (root != NULL) {
        found = timSinhVienTheoMaLop(root, maLop) || found;
        found = timVaHienThiTatCaSinhVienTheoMaLop(root->left, maLop) || found;
        found = timVaHienThiTatCaSinhVienTheoMaLop(root->right, maLop) || found;
    }

    return found;
}

// H�m t�m v? tr� l?p trong danh s�ch l?p d?a v�o m� l?p
int timViTriLopTheoMaLop(Lop danhSachLop[], int soLuongLop, int maLop) {
    for (int i = 0; i < soLuongLop; i++) {
        if (danhSachLop[i].maLop == maLop) {
            return i;
        }
    }
    return -1; // Tr? v? -1 n?u kh�ng t�m th?y m� l?p trong danh s�ch
}

// H�m x�a m?t l?p ra kh?i danh s�ch
int xoaLop(Lop danhSachLop[], int* soLuongLop, int maLop) {
    int viTriLop = timViTriLopTheoMaLop(danhSachLop, *soLuongLop, maLop);
    if (viTriLop == -1) {
        return 0; // Kh�ng t�m th?y m� l?p trong danh s�ch
    }

    // D?i c�c l?p sau v? tru?c m?t bu?c
    for (int i = viTriLop; i < *soLuongLop - 1; i++) {
        danhSachLop[i] = danhSachLop[i + 1];
    }

    (*soLuongLop)--; // Gi?m s? lu?ng l?p sau khi x�a

    return 1; // X�a l?p th�nh c�ng
}

// H�m t�m di?m trung b�nh l?n nh?t trong c�y nh? ph�n t�m ki?m
float timDiemTrungBinhLonNhat(Node* root, float* diemTBMax) {
    if (root == NULL) {
        return *diemTBMax;
    }

    // Duy?t qua c�y nh? ph�n t�m ki?m theo th? t? trung tuy?n (left - root - right)
    timDiemTrungBinhLonNhat(root->left, diemTBMax);
    if ((root->sinhVien.diemToan >= 0) && (root->sinhVien.diemLy >= 0) && (root->sinhVien.diemHoa >= 0)) {
        float diemTB = (root->sinhVien.diemToan + root->sinhVien.diemLy + root->sinhVien.diemHoa) / 3.0;
        if (diemTB > *diemTBMax) {
            *diemTBMax = diemTB;
        }
    }
    timDiemTrungBinhLonNhat(root->right, diemTBMax);

    return *diemTBMax;
}

// H�m hi?n th? t?t c? sinh vi�n c� di?m trung b�nh l?n nh?t
void hienThiTatCaSinhVienDiemTBMax(Node* root, float diemTBMax) {
    if (root == NULL) {
        return;
    }

    hienThiTatCaSinhVienDiemTBMax(root->left, diemTBMax);
    if ((root->sinhVien.diemToan >= 0) && (root->sinhVien.diemLy >= 0) && (root->sinhVien.diemHoa >= 0)) {
        float diemTB = (root->sinhVien.diemToan + root->sinhVien.diemLy + root->sinhVien.diemHoa) / 3.0;
        if (diemTB == diemTBMax) {
            hienThiThongTinMotSinhVien(root->sinhVien);
        }
    }
    hienThiTatCaSinhVienDiemTBMax(root->right, diemTBMax);
}

// H�m t�m di?m trung b�nh l?n nh?t trong 1 l?p
float timDiemTrungBinhLonNhatTrongLop(Node* root, int maLop, float* diemTBMax) {
    if (root == NULL) {
        return *diemTBMax;
    }

    // Duy?t qua c�y nh? ph�n t�m ki?m theo th? t? trung tuy?n (left - root - right)
    timDiemTrungBinhLonNhatTrongLop(root->left, maLop, diemTBMax);
    if ((root->sinhVien.maLop == maLop) &&
        (root->sinhVien.diemToan >= 0) &&
        (root->sinhVien.diemLy >= 0) &&
        (root->sinhVien.diemHoa >= 0)) {
        float diemTB = (root->sinhVien.diemToan + root->sinhVien.diemLy + root->sinhVien.diemHoa) / 3.0;
        if (diemTB > *diemTBMax) {
            *diemTBMax = diemTB;
        }
    }
    timDiemTrungBinhLonNhatTrongLop(root->right, maLop, diemTBMax);

    return *diemTBMax;
}

// H�m hi?n th? t?t c? sinh vi�n c� di?m trung b�nh l?n nh?t trong 1 l?p
void hienThiTatCaSinhVienDiemTBMaxTrongLop(Node* root, int maLop, float diemTBMax) {
    if (root == NULL) {
        return;
    }

    hienThiTatCaSinhVienDiemTBMaxTrongLop(root->left, maLop, diemTBMax);
    if ((root->sinhVien.maLop == maLop) &&
        (root->sinhVien.diemToan >= 0) &&
        (root->sinhVien.diemLy >= 0) &&
        (root->sinhVien.diemHoa >= 0)) {
        float diemTB = (root->sinhVien.diemToan + root->sinhVien.diemLy + root->sinhVien.diemHoa) / 3.0;
        if (diemTB == diemTBMax) {
            hienThiThongTinMotSinhVien(root->sinhVien);
        }
    }
    hienThiTatCaSinhVienDiemTBMaxTrongLop(root->right, maLop, diemTBMax);
}

int hienThiMenu() {
    int choice;
    printf("\nChon chuc nang:\n");
    printf("1. Them 1 lop moi.\n");
    printf("2. Them 1 sinh vien.\n");
    printf("3. Tim sinh vien theo ma SV.\n");
    printf("4. Luu danh sach sien vien lop vao file.\n");
    printf("5. Hien thi danh sach sv trong file.\n");
    printf("6. Tim sv theo ten.\n");
	printf("7. Hien thi danh sach sv theo ma lop.\n");
	printf("8. Xoa sinh vien.\n");
	printf("9. Xoa lop.\n");
	printf("10.Sinh vien co diem TB cao nhat.\n");
	printf("11.Sinh vien co diem TB cao nhat trong 1 lop.\n");
    printf("0. Thoat.\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    Node* root = NULL; // C�y nh? ph�n t�m ki?m ch?a danh s�ch sinh vi�n
    Lop danhSachLop[10]; // M?ng ch?a danh s�ch l?p
    int soLuongLop = 0; // S? lu?ng l?p hi?n t?i trong danh s�ch

    int choice;
    do {
        choice = hienThiMenu();
        switch (choice) {
            case 1:
                themLop(danhSachLop, &soLuongLop);
                break;
            case 2:
                themSinhVien(&root, danhSachLop, soLuongLop);
                break;
            case 3:
				if (root == NULL) {
				    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
				} else {
				    char maSVTimKiem[10];
				    printf("Nhap ma sinh vien can tim: ");
				    scanf("%s", maSVTimKiem);
				    Node* foundSinhVien = searchSinhVien(root, maSVTimKiem);
				    hienThiThongTinSinhVien(foundSinhVien, danhSachLop, soLuongLop);
				}
				break;
				case 4: {
                // Luu danh s�ch sinh vi�n v�o file
                FILE* fileSinhVien = fopen("danhsachsinhvien.txt", "w");
                if (fileSinhVien == NULL) {
                    printf("Khong the mo file de ghi.\n");
                    break;
                }

                ghiDanhSachSinhVien(fileSinhVien, root);

                fclose(fileSinhVien);

                // Luu danh s�ch l?p v�o file
                FILE* fileLop = fopen("danhsachlop.txt", "w");
                if (fileLop == NULL) {
                    printf("Khong the mo file de ghi.\n");
                    break;
                }

                ghiDanhSachLop(fileLop, danhSachLop, soLuongLop);

                fclose(fileLop);

                printf("Luu danh sach sinh vien-lop vao file thanh cong.\n");
                break;
                }
	            case 5: {
	                // Hi?n th? danh s�ch sinh vi�n theo m� sinh vi�n tang d?n
	                if (root == NULL) {
	                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
	                } else {
	                    printf("Danh sach sinh vien theo ma SV tang dan:\n");
	                    hienThiDanhSachSinhVienTheoMaSV(root);
	                }
	                break;
	            }
	                        case 6: {
                // T�m v� hi?n th? t?t c? sinh vi�n theo t�n
                if (root == NULL) {
                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
                } else {
                    char tenSVCanTim[255];
                    printf("Nhap ten sinh vien can tim: ");
                    scanf(" %[^\n]", tenSVCanTim);
                    timVaHienThiTatCaSinhVienTheoTen(root, tenSVCanTim);
                }
                break;
                }
            	 case 7: {
                // T�m v� hi?n th? t?t c? sinh vi�n theo m� l?p
                if (root == NULL) {
                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
                } else {
                    int maLopCanTim;
                    printf("Nhap ma lop can tim: ");
                    scanf("%d", &maLopCanTim);
                    timVaHienThiTatCaSinhVienTheoMaLop(root, maLopCanTim);
                }
                break;
                }
                
                case 8: {
                // X�a m?t sinh vi�n ra kh?i danh s�ch
                if (root == NULL) {
                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
                } else {
                    char maSVCanXoa[10];
                    printf("Nhap ma sinh vien can xoa: ");
                    scanf("%s", maSVCanXoa);

                    root = xoaSinhVien(root, maSVCanXoa);
                    printf("Da xoa sinh vien co ma SV: %s\n", maSVCanXoa);
                }
                break;
            }
            case 9: {
                // X�a m?t l?p ra kh?i danh s�ch
                if (soLuongLop == 0) {
                    printf("Danh sach lop trong. Vui long them lop truoc.\n");
                } else {
                    int maLopCanXoa;
                    printf("Nhap ma lop can xoa: ");
                    scanf("%d", &maLopCanXoa);

                    int ketQuaXoa = xoaLop(danhSachLop, &soLuongLop, maLopCanXoa);
                    if (ketQuaXoa) {
                        printf("Da xoa lop co ma Lop: %d\n", maLopCanXoa);
                    } else {
                        printf("Khong tim thay lop co ma Lop: %d\n", maLopCanXoa);
                    }
                }
                break;
            }
            case 10: {
                // T�m v� hi?n th? t?t c? sinh vi�n c� di?m trung b�nh l?n nh?t
                if (root == NULL) {
                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
                } else {
                    float diemTBMax = -1;
                    diemTBMax = timDiemTrungBinhLonNhat(root, &diemTBMax);
                    printf("Diem trung binh lon nhat: %.2f\n", diemTBMax);

                    printf("Danh sach sinh vien co diem trung binh lon nhat:\n");
                    hienThiTatCaSinhVienDiemTBMax(root, diemTBMax);
                }
                break;
            }
            
            case 11: {
                // T�m v� hi?n th? t?t c? sinh vi�n c� di?m trung b�nh l?n nh?t trong 1 l?p
                if (root == NULL) {
                    printf("Danh sach sinh vien trong. Vui long them sinh vien truoc.\n");
                } else {
                    int maLopCanTim;
                    printf("Nhap ma lop can tim: ");
                    scanf("%d", &maLopCanTim);

                    float diemTBMax = -1;
                    diemTBMax = timDiemTrungBinhLonNhatTrongLop(root, maLopCanTim, &diemTBMax);
                    printf("Diem trung binh lon nhat trong lop: %.2f\n", diemTBMax);

                    printf("Danh sach sinh vien co diem trung binh lon nhat trong lop:\n");
                    hienThiTatCaSinhVienDiemTBMaxTrongLop(root, maLopCanTim, diemTBMax);
                }
                break;
            }

            case 0:
                printf("Tam biet.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    // TODO: X�a c�y nh? ph�n t�m ki?m v� gi?i ph�ng b? nh?

    return 0;
}

