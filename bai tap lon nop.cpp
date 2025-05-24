#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATG 10
#define TENGAME 50
#define THELOAI 30

// kiểu cấu trúc struct type , TroChoi là tên để khai báo rõ ràng mà ko cần lặp lại struct
typedef struct {
    char maTG[MATG];
    char tenGame[TENGAME];
    char theLoai[THELOAI];
    int giaGoc;   // Giá gốc do người dùng nhập
    int giaKM;    // Giá sau khi áp dụng khuyến mãi (luôn <= giá gốc)
    int khuyenMai;  // Phần trăm khuyến mãi (0-100)
} TroChoi;

//đây là 1 cấu trúc tự tham chiếu vì bên trong nó chứa 1 con trỏ struct Node* next.Node thứ 2 y chang trên
typedef struct Node {
    TroChoi data;
    struct Node* next;
} Node;

// *: truy cập và duyệt qua danh sách hoặc thay đổi dữ liệu bên trong các nút của danh sách, nhưng không thay đổi chính con trỏ head
// **: khi muốn thay đổi chính con trỏ head
void themGame(Node** head);
void hienThiDS(Node* head);
void sapXepTheoGia(Node* head);
void timKiemTheoMa(Node* head);
void timKiemTheoTen(Node* head);
void timKiemTheoTheLoai(Node* head);
void timKiemTheoGiaGoc(Node* head);
void xoaGame(Node** head);
void apDungKhuyenMai(Node** head);
void huyKhuyenMai(Node** head);
void ghiFile(Node* head);
void docFile(Node** head);
void freeList(Node** head);

int main() {
    Node* head = NULL;// tạo 1 danh sách head rỗng
    int choice;
    do {
        printf("\n=== QUAN LY CUA HANG GAME ===\n");
        printf("1. Them tro choi\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Sap xep theo gia ban\n");
        printf("4. Tim kiem theo ma tro choi\n");
        printf("5. Xoa tro choi\n");
        printf("6. Ap dung khuyen mai\n");
        printf("7. Huy khuyen mai\n");
        printf("8. Ghi danh sach ra file\n");
        printf("9. Doc danh sach tu file\n");
        printf("0. Thoat\n");
        printf("\nChon chuc nang: ");
        scanf("%d", &choice);
        getchar();    

        switch(choice) {
            case 1: 
            	printf("Chao ban den chuc nang them game  \n");
                themGame(&head); 
                break;
            case 2: 
        	    printf("Chao ban den chuc nang hien thi  \n");
                hienThiDS(head); 
                break;
            case 3: 
            	printf("Chao ban den chuc nang sap xep theo gia\n");
            	sapXepTheoGia(head);
                break;
            case 4: 
                printf("Chao ban den chuc nang tim kiem\n");
                printf("Nhan 1 : neu muon tim kiem theo ma\n");
                printf("Nhan 2 : neu muon tim kiem theo ten \n");
                printf("Nhan 3 : neu muon tim kiem theo the loai \n");
                printf("Nhan 4 : neu muon tim kiem theo gia goc\n");
                int a;
                printf("Ban muon tim kiem gi : ");
                scanf("%d",&a);
                switch(a){
                	case 1:
                		printf("Chao ban den chuc nang tim kiem theo ma\n");
                		timKiemTheoMa(head);
                		break;
					case 2:
						printf("Chao ban den chuc nang tim kiem theo ten \n");
                		timKiemTheoTen(head);
                		break;
                	case 3:
                		printf("Chao ban den chuc nang tim kiem theo the loai\n");
                		timKiemTheoTheLoai(head);
                		break;
                	case 4:
                		printf("Chao ban den chuc nang tim kiem theo gia goc \n");
                		timKiemTheoGiaGoc(head);
                		break;
                	default:
                		printf("Lua chon khong dung!!!");
				}
                break;
            case 5: 
            	printf("Chao ban den chuc nang xoa \n");
                xoaGame(&head); 
                break;
            case 6: 
            	printf("Chao ban den chuc nang khuyen mai \n");
                apDungKhuyenMai(&head); 
                break;
            case 7: 
                printf("Chao ban den chuc nang huy khuyen mai \n");
                huyKhuyenMai(&head); 
                break;
            case 8: 
                printf("Chao ban den chuc nang ghi file \n");
                ghiFile(head); 
                break;
            case 9: 
            	printf("Chao ban den chuc nang doc file \n");
                docFile(&head); 
                break;
            case 0: 
                printf("Da thoat.\n"); 
                break;
            default:
			    printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    freeList(&head);
    return 0;
}

// 1. Thêm trò chơi vào danh sách liên kết
void themGame(Node** head) {
	// cấp phát bộ nhớ
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Khong du bo nho!\n");
        return;
    }
    
    // Khởi tạo giá trị mặc định
    newNode->data.khuyenMai = 0;

    printf("Nhap ma tro choi: ");
    fgets(newNode->data.maTG, sizeof(newNode->data.maTG), stdin);
    newNode->data.maTG[strcspn(newNode->data.maTG, "\n")] = 0;
   
    printf("Nhap ten tro choi: ");
    fgets(newNode->data.tenGame, sizeof(newNode->data.tenGame), stdin);
    newNode->data.tenGame[strcspn(newNode->data.tenGame, "\n")] = 0;
  
    printf("Nhap the loai: ");
    fgets(newNode->data.theLoai, sizeof(newNode->data.theLoai), stdin);
    newNode->data.theLoai[strcspn(newNode->data.theLoai, "\n")] = 0;
  
    printf("Nhap gia goc: ");
    scanf("%d", &newNode->data.giaGoc);
    getchar();
    
    // Ban đầu giá KM = giá gốc (chưa có khuyến mãi)
    newNode->data.giaKM = newNode->data.giaGoc;

    newNode->next = *head;// gán nút đầu tiên bây giờ =  nút tiếp theo của newNode
    *head = newNode;//gán newNode =  head

    printf("Da them tro choi thanh cong!\n");
}

// 2. Hiển thị danh sách
void hienThiDS(Node* head) {
    if (!head) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-10s %-10s %-10s\n", 
          "Ma TG", "Ten Game", "The Loai", "Gia Goc", "KM(%)", "Gia KM");
    printf("======================================================================================\n");

    Node* current = head;
    while (current) {
        printf("%-10s %-20s %-15s %-10d %-10d %-10d\n",
               current->data.maTG,
               current->data.tenGame,
               current->data.theLoai,
               current->data.giaGoc,
               current->data.khuyenMai,
               current->data.giaKM);
        current = current->next;// giúp di chuyển con trỏ tới nút tiếp theo trong danh sách
    }
}

// Các hàm hỗ trợ cho merge sort (giữ nguyên)
void splitList(Node* source, Node** front, Node** back) {
    Node* fast;
    Node* slow;
    slow = source;// bắt đầu ở đầu danh sách
    fast = source->next;//  bắt đầu ở nút thứ 2 
    
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *front = source;// Dòng này gán giá trị của source (tức là địa chỉ của nút đầu tiên của danh sách ban đầu) vào vị trí mà front đang trỏ tới.
    *back = slow->next;// sau khi kết thúc vòng lặp thì slow sẽ đến giữa danh sách nên slow-> là phần tư tiếp theo cho tới cuối danh sách
    slow->next = NULL;// cắt dứt liên kết giữa 2 danh sách sau khi phân chia, slow trỏ tới nut tiếp theo nó sẽ trỏ tới null
}

Node* merge(Node* a, Node* b) {
    Node* result = NULL;
    
    if (a == NULL) return b;
    else if (b == NULL) return a;
    if (a->data.giaKM <= b->data.giaKM) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }
    
    return result;
}

void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;
    
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    
    splitList(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = merge(a, b);
}

// 3. Sắp xếp theo giá bán (giá KM)
void sapXepTheoGia(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    
    mergeSort(&head);
    printf("Da sap xep danh sach theo gia khuyen mai!\n");
    hienThiDS(head);
}

// 4.1 Tìm kiếm trò chơi theo mã
void timKiemTheoMa(Node* head) {
    char ma[MATG];
    printf("Nhap ma tro choi can tim: ");
    scanf("%s", ma);

    Node* current = head;
    while (current) {
        if (strcmp(current->data.maTG, ma) == 0) {
            printf("\n%-10s %-20s %-15s %-10s %-10s %-10s\n", 
                  "Ma TG", "Ten Game", "The Loai", "Gia Goc", "KM(%)", "Gia KM");
            printf("==============================================================================\n");
            printf("%-10s %-20s %-15s %-10d %-10d %-10d\n",
                   current->data.maTG,
                   current->data.tenGame,
                   current->data.theLoai,
                   current->data.giaGoc,
                   current->data.khuyenMai,
                   current->data.giaKM);
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay tro choi co ma %s\n", ma);
}

// 4.2 Tìm kiếm trò chơi theo tên
void timKiemTheoTen(Node* head) {
    char ten[TENGAME];
    printf("Nhap ten game tro choi can tim: ");
    scanf("%s", ten);

    Node* current = head;
    while (current) {
        if (strcmp(current->data.tenGame, ten) == 0) {
            printf("\n%-10s %-20s %-15s %-10s %-10s %-10s\n", 
                  "Ma TG", "Ten Game", "The Loai", "Gia Goc", "KM(%)", "Gia KM");
            printf("=============================================================================\n");
            printf("%-10s %-20s %-15s %-10d %-10d %-10d\n",
                   current->data.maTG,
                   current->data.tenGame,
                   current->data.theLoai,
                   current->data.giaGoc,
                   current->data.khuyenMai,
                   current->data.giaKM);
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay tro choi co ten game %s\n", ten);
}

// 4.3 Tìm kiếm trò chơi theo the loai
void timKiemTheoTheLoai(Node* head) {
    char theLoai[THELOAI];
    printf("Nhap the loai tro choi can tim: ");
    scanf("%s", theLoai);

    Node* current = head;
    while (current) {
        if (strcmp(current->data.theLoai, theLoai) == 0) {
            printf("\n%-10s %-20s %-15s %-10s %-10s %-10s\n", 
                  "Ma TG", "Ten Game", "The Loai", "Gia Goc", "KM(%)", "Gia KM");
            printf("==============================================================================\n");
            printf("%-10s %-20s %-15s %-10d %-10d %-10d\n",
                   current->data.maTG,
                   current->data.tenGame,
                   current->data.theLoai,
                   current->data.giaGoc,
                   current->data.khuyenMai,
                   current->data.giaKM);
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay tro choi co the loai %s\n", theLoai);
}

// 4.4 Tìm kiếm trò chơi theo gia goc
void timKiemTheoGiaGoc(Node* head) {
    int gia;
    printf("Nhap gia goc cua tro choi can tim: ");
    scanf("%d", gia);

    Node* current = head;
    while (current) {
        if (current->data.giaGoc == gia ) {
            printf("\n%-10s %-20s %-15s %-10s %-10s %-10s\n", 
                  "Ma TG", "Ten Game", "The Loai", "Gia Goc", "KM(%)", "Gia KM");
            printf("===============================================================================\n");
            printf("%-10s %-20s %-15s %-10d %-10d %-10d\n",
                   current->data.maTG,
                   current->data.tenGame,
                   current->data.theLoai,
                   current->data.giaGoc,
                   current->data.khuyenMai,
                   current->data.giaKM);
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay tro choi co gia goc %s\n", gia);
}

// 5. Xóa trò chơi theo mã
void xoaGame(Node** head) {
    char ma[MATG];
    printf("Nhap ma tro choi can xoa: ");
    scanf("%s", ma);

    Node* current = *head;
    Node* xoa = NULL;
    while (current) {
        if (strcmp(current->data.maTG, ma) == 0) {
            if (!xoa) {
                *head = current->next;
            } else {
                xoa->next = current->next;
            }
            free(current);
            printf("Da xoa tro choi co ma %s\n", ma);
            return;
        }
        xoa = current;
        current = current->next;
    }

    printf("Khong tim thay tro choi de xoa.\n");
}

// 6. Áp dụng khuyến mãi (chỉ giảm giá)
void apDungKhuyenMai(Node** head) {
    char maGame[MATG];
    int phanTramKM;
    
    printf("Nhap ma tro choi can ap dung khuyen mai: ");
    fgets(maGame, MATG, stdin);
    maGame[strcspn(maGame, "\n")] = '\0';
    
    printf("Nhap phan tram khuyen mai (0-100): ");
    scanf("%d", &phanTramKM);
    getchar();
    
    // Kiểm tra phần trăm khuyến mãi hợp lệ
    if (phanTramKM < 0 || phanTramKM > 100) {
        printf("Phan tram khuyen mai khong hop le! (phai tu 0 den 100)\n");
        return;
    }
    
    Node* current = *head;
    while(current != NULL) {
        if(strcmp(current->data.maTG, maGame) == 0) {
            // Cập nhật phần trăm khuyến mãi
            current->data.khuyenMai = phanTramKM;
            
            // Tính giá KM = giá gốc * (100 - phần trăm KM) / 100
            current->data.giaKM = current->data.giaGoc * (100 - phanTramKM) / 100;
            
            // Đảm bảo giá KM không âm
            if (current->data.giaKM < 0) {
                current->data.giaKM = 0;
            }
            
            printf("Da ap dung khuyen mai %d%% cho tro choi %s\n", 
                  phanTramKM, current->data.tenGame);
            printf("Gia goc: %.2f\n", current->data.giaGoc);
            printf("Gia khuyen mai: %.2f\n", current->data.giaKM);
            return;
        }
        current = current->next;
    }
    
    printf("Khong tim thay tro choi co ma %s\n", maGame);
}

// 7. Hủy khuyến mãi (trở về giá gốc)
void huyKhuyenMai(Node** head) {
    char maGame[MATG];
    printf("Nhap ma tro choi can huy khuyen mai: ");
    fgets(maGame, MATG, stdin);
    maGame[strcspn(maGame, "\n")] = '\0';
    
    Node* current = *head;
    while(current != NULL) {
        if(strcmp(current->data.maTG, maGame) == 0) {
            if(current->data.khuyenMai != 0) {
                current->data.giaKM = current->data.giaGoc;
                current->data.khuyenMai = 0;
                printf("Da huy khuyen mai cho tro choi %s\n", current->data.tenGame);
                printf("Gia tro ve gia goc: %.2f\n", current->data.giaKM);
            } else {
                printf("Tro choi nay khong co khuyen mai\n");
            }
            return;
        }
        current = current->next;
    }
    
    printf("Khong tim thay tro choi co ma %s\n", maGame);
}

// 8. Ghi danh sách vào file
void ghiFile(Node* head) {
    FILE* f = fopen("game.txt", "w");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return;
    }

    Node* current = head;
    while (current) {
        fprintf(f, "%s,%s,%s,%d,%d,%d\n",
            current->data.maTG,
            current->data.tenGame,
            current->data.theLoai,
            current->data.giaGoc,
            current->data.giaKM,
            current->data.khuyenMai);
        current = current->next;
    }

    fclose(f);
    printf("Da ghi danh sach vao file game.txt\n");
}

// 9. Đọc danh sách từ file
void docFile(Node** head) {
    FILE* f = fopen("game.txt", "r");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return;
    }

    freeList(head);
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;
        
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) {
            printf("Khong du bo nho!\n");
            break;
        }
        
        // Phân tích dòng dữ liệu
        char* token = strtok(line, ",");
        int field = 0;
        while (token != NULL) {
            switch(field) {
                case 0: strncpy(newNode->data.maTG, token, MATG-1); break;
                case 1: strncpy(newNode->data.tenGame, token, TENGAME-1); break;
                case 2: strncpy(newNode->data.theLoai, token, THELOAI-1); break;
                case 3: newNode->data.giaGoc = atof(token); break;
                case 4: newNode->data.giaKM = atof(token); break;
                case 5: newNode->data.khuyenMai = atoi(token); break;
            }
            token = strtok(NULL, ",");
            field++;
        }
        
        newNode->next = *head;
        *head = newNode;
    }

    fclose(f);
    printf("Da doc danh sach tu file game.txt\n");
}

// Giải phóng bộ nhớ
void freeList(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}