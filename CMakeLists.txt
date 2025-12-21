# Tên dự án, tuân thủ yêu cầu đặt tên trong tài liệu
cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceManager LANGUAGES CXX)

# Thiết lập chuẩn C++ (Sử dụng C++11 hoặc C++14 trở lên là khuyến nghị tốt)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Định nghĩa các thư mục chính
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Tự động tìm tất cả các file nguồn (.cpp) trong thư mục src/
# Điều này bao gồm: main.cpp, Income.cpp, Expense.cpp, Wallet.cpp, v.v.
file(GLOB_RECURSE PROJECT_SOURCES
    "${SOURCE_DIR}/*.cpp"
)

# Thêm thư mục include/ vào đường dẫn tìm kiếm header
include_directories(${INCLUDE_DIR})

# Tạo tệp thực thi (executable)
# Tên file thực thi sẽ là PersonalFinanceManager
add_executable(PersonalFinanceManager ${PROJECT_SOURCES})

# Thiết lập thư mục đầu ra cho file thực thi (tùy chọn, thường là build/bin)
set_target_properties(PersonalFinanceManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)