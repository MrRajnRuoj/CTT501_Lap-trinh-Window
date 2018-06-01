- Họ và tên: Nguyễn Trọng An 
- MSSV: 1653107 
- Lớp: 16CLC2

- Các yêu cầu đã hoàn thành:
+ New text: Tạo cửa sổ con cho phép edit text. Title là “Text n” (n: là số tăng liên tiếp 1,2,3…)
+ New bitmap: Tạo cửa sổ con cho phép vẽ hình. Title là “Bitmap n” (n: là số tăng liên tiếp 1,2,3…)
+ Edit: Nhóm menu dùng cho cửa sổ loại text. Khi active cửa sổ loại text, nhóm menu Draw sẽ disable
+ Draw: Nhóm menu dùng cho cửa sổ loại bitmap. Khi active cửa sổ loại bitmap, nhóm menu Edit sẽ disable
+ Choose color: Chọn màu Dùng chung cho cả hai loại cửa sổ text và bitmap
+ Choose font: Chọn font Chỉ dùng cho cửa sổ loại text. Khi active cửa sổ loại bitmap thì chức năng này bị disable
+ Window: Nhóm menu dùng để sắp xếp và quản lý các child window. Dùng chung cho cả hai loại cửa sổ text và bitmap

- Các yêu cầu chưa hoàn thành: Yêu cầu nâng cao
+ Lưu hình vẽ trong cửa sổ bitman và khôi phục ngữ cảnh tương ứng khi active child window
+ Cập nhật WM_PAINT trong cửa sổ bitman

- Version Visual Studio build chương trình: Visual Studio 15
- Các lưu ý khác khi build và chạy chương trình: Build trên platform x64
