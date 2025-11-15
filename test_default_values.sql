-- 测试默认值设置的SQL脚本
-- 本脚本用于演示哪些默认值设置是正确的，哪些是错误的

-- 测试1：ENUM类型的默认值
-- ✅ 正确：ENUM类型使用ENUM值作为默认值
CREATE TABLE test_enum_correct (
    id INT AUTO_INCREMENT PRIMARY KEY,
    status ENUM('PENDING','APPROVED','REJECTED') DEFAULT 'PENDING'
);

-- ❌ 错误：ENUM类型不能使用CURRENT_TIMESTAMP作为默认值
-- 以下语句会报错：Invalid default value for 'status'
-- CREATE TABLE test_enum_wrong (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     status ENUM('PENDING','APPROVED','REJECTED') DEFAULT CURRENT_TIMESTAMP
-- );

-- 测试2：TIMESTAMP类型的默认值
-- ✅ 正确：TIMESTAMP可以使用CURRENT_TIMESTAMP
CREATE TABLE test_timestamp_correct (
    id INT AUTO_INCREMENT PRIMARY KEY,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- 测试3：BOOLEAN类型的默认值
-- ✅ 正确：BOOLEAN可以使用TRUE/FALSE或1/0
CREATE TABLE test_boolean_correct (
    id INT AUTO_INCREMENT PRIMARY KEY,
    is_active BOOLEAN DEFAULT TRUE,
    is_confirmed BOOLEAN DEFAULT FALSE,
    is_deleted BOOLEAN DEFAULT 0
);

-- 测试4：VARCHAR类型的默认值
-- ✅ 正确：VARCHAR可以使用字符串字面量
CREATE TABLE test_varchar_correct (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) DEFAULT 'Unknown',
    description VARCHAR(200) DEFAULT ''
);

-- 测试5：数值类型的默认值
-- ✅ 正确：数值类型可以使用数值字面量
CREATE TABLE test_numeric_correct (
    id INT AUTO_INCREMENT PRIMARY KEY,
    count INT DEFAULT 0,
    price DECIMAL(10,2) DEFAULT 0.00,
    rate FLOAT DEFAULT 0.0
);

-- 清理测试表
DROP TABLE IF EXISTS test_enum_correct;
DROP TABLE IF EXISTS test_timestamp_correct;
DROP TABLE IF EXISTS test_boolean_correct;
DROP TABLE IF EXISTS test_varchar_correct;
DROP TABLE IF EXISTS test_numeric_correct;

-- ============================================================================
-- 结论：
-- 1. ENUM类型只能使用ENUM定义中的值作为默认值
-- 2. ENUM类型不能使用CURRENT_TIMESTAMP、NOW()等函数作为默认值
-- 3. TIMESTAMP类型可以使用CURRENT_TIMESTAMP作为默认值
-- 4. BOOLEAN类型可以使用TRUE/FALSE/1/0作为默认值
-- 5. 字符串类型可以使用字符串字面量作为默认值
-- 6. 数值类型可以使用数值字面量作为默认值
-- ============================================================================
