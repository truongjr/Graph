# CTDL & GT - Đồ án Đồ Thị - PTITHCM 
## Yêu cầu
 - Nhập đồ thị có hướng có trọng số qua giao diện, có thể thêm, xóa sửa lại đỉnh, cung, trọng số ( trên màn hình hiện thị ma trận kế tương ứng). 
 - Lưu đồ thị vào file sao cho ta có thể vẽ lại đồ thị về sau này. 
 - Demo giải thuật DFS, BFS 
 - Tính số thành phần liên thông của đồ thị? Và liệt kê các đỉnh trong từng thành phần liên thông 
 - Tìm đường đi ngắn nhất từ đỉnh X đến đỉnh Y, có demo trên hình và in ra đường đi cụ thể. 
 - Tìm tất cả đỉnh trụ , đinh thắt và cạnh cầu của đồ thị. 
 - Tìm các chu trình Hamilton, và chu trình Euler của đồ thị (nếu có) 
 - Demo thuật toán Topo Sort
## Cài đặt
1. Đồ án sử dụng thư viện giao diện winbgim.h, chạy trên IDE DevC++.
2. Cài đặt thư viện winbgim. Xem hướng dẫn cài đặt tại đây
3. Tải về và giải nén source code.
4. Mở file DoThi.exe.dev bằng DevC++ và run project.
Lưu ý: Đồ án hiển thị trên màn hình Full HD (1920x1080), cỡ chữ 100%.

## Đồ án đồ thị này vẫn còn 1 số chỗ chưa hoàn chỉnh:
- Lúc nhập tên đỉnh hoặc nhập trọng số của cung thì không nên bắt buộc người dùng nhập đúng 2 số. Ví dụ: khi nhập "1" rồi ấn enter thì nên nhận luôn giá trị đó.
- Khi nhập tên "00" thì nên báo cho người dùng biết rằng đã nhập sai, yêu cầu người dùng nhập lại.
- Lúc save và nhập tên file nên đưa ra cảnh báo người dùng hỏi người dùng có ghi đè trong trường hợp nhập trùng tên file đã có trong thư mục saves không.
- Các thuật toán nên được cải thiện với các số liệu lớn hơn.
- Giao diện save nên tích hợp chung với open.
- Khi ấn open, và chọn 1 file bất kì, nên tích hợp thêm chức năng click đúp chuột để mở file.
## Một số hình ảnh
![image](https://user-images.githubusercontent.com/62049245/155195999-a16d824b-8b18-432b-8aa2-2a47d4d5809e.png)

![image](https://user-images.githubusercontent.com/62049245/155196165-66d89e43-207e-43cd-8065-6189aedcf749.png)

![image](https://user-images.githubusercontent.com/62049245/155196279-c03623a3-c7b6-4d00-af8c-8d208b8561c1.png)

![image](https://user-images.githubusercontent.com/62049245/155196382-093d0222-5baf-4c60-80d0-51549f101e74.png)

