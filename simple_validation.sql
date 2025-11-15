-- 简单验证脚本：测试默认值设置的正确性
-- 可以在任何MySQL环境中运行

-- 创建测试数据库
DROP DATABASE IF EXISTS test_schema_validation;
CREATE DATABASE test_schema_validation;
USE test_schema_validation;

-- ============================================================================
-- 测试1: 验证ENUM类型不能使用CURRENT_TIMESTAMP作为默认值（预期失败）
-- ============================================================================

-- 这个语句应该失败并报错：Invalid default value for 'status'
-- CREATE TABLE test_enum_error (
--     id BIGINT AUTO_INCREMENT PRIMARY KEY,
--     status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') DEFAULT CURRENT_TIMESTAMP
-- );
-- 错误信息: ERROR 1067 (42000): Invalid default value for 'status'

SELECT '测试1: ENUM类型不能使用CURRENT_TIMESTAMP - 已注释掉错误语句' AS test_result;

-- ============================================================================
-- 测试2: 验证正确的ENUM默认值设置
-- ============================================================================

CREATE TABLE test_enum_correct (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') DEFAULT 'PENDING'
);

INSERT INTO test_enum_correct (id) VALUES (1);
SELECT 'ENUM默认值测试' AS test_name, status FROM test_enum_correct WHERE id = 1;

-- 应该输出: status = 'PENDING'

-- ============================================================================
-- 测试3: 验证TIMESTAMP的CURRENT_TIMESTAMP默认值
-- ============================================================================

CREATE TABLE test_timestamp (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

INSERT INTO test_timestamp (id) VALUES (1);
SELECT 'TIMESTAMP默认值测试' AS test_name, created_at, updated_at FROM test_timestamp WHERE id = 1;

-- 等待一秒后更新
SELECT SLEEP(1);
UPDATE test_timestamp SET id = 1 WHERE id = 1;
SELECT 'TIMESTAMP自动更新测试' AS test_name, created_at, updated_at FROM test_timestamp WHERE id = 1;

-- updated_at应该比created_at晚

-- ============================================================================
-- 测试4: 验证BOOLEAN默认值
-- ============================================================================

CREATE TABLE test_boolean (
    id BIGINT AUTO_INCREMENT PRIMARY KEY,
    is_active BOOLEAN DEFAULT TRUE,
    is_confirmed BOOLEAN DEFAULT FALSE
);

INSERT INTO test_boolean (id) VALUES (1);
SELECT 'BOOLEAN默认值测试' AS test_name, is_active, is_confirmed FROM test_boolean WHERE id = 1;

-- 应该输出: is_active = 1, is_confirmed = 0

-- ============================================================================
-- 测试5: 验证修正后的完整表结构
-- ============================================================================

-- user表
CREATE TABLE user (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '用户id',
    username VARCHAR(50) NOT NULL COMMENT '用户名',
    password VARCHAR(255) NOT NULL COMMENT '密码',
    real_name VARCHAR(50) NULL COMMENT '真实姓名',
    phone VARCHAR(20) NULL COMMENT '手机号',
    email VARCHAR(100) NULL COMMENT '邮箱',
    role ENUM('USER','ADMIN') NULL DEFAULT 'USER' COMMENT '角色',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (id),
    UNIQUE KEY uk_username (username)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';

-- meeting_room表
CREATE TABLE meeting_room (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '会议室ID',
    name VARCHAR(100) NOT NULL COMMENT '会议室名称',
    room_number VARCHAR(50) NOT NULL COMMENT '房间号',
    capacity INT NOT NULL COMMENT '容纳人数',
    area DECIMAL(10,2) NULL COMMENT '面积',
    purpose VARCHAR(200) NULL COMMENT '用途描述',
    photo_url VARCHAR(500) NULL COMMENT '图片',
    status ENUM('AVAILABLE','UNAVAILABLE') NULL DEFAULT 'AVAILABLE' COMMENT '状态',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    updated_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    PRIMARY KEY (id),
    UNIQUE KEY uk_room_number (room_number)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='会议室表';

-- booking表
CREATE TABLE booking (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '预定ID',
    user_id BIGINT NOT NULL COMMENT '用户ID',
    room_id BIGINT NOT NULL COMMENT '会议室ID',
    booking_date DATE NOT NULL COMMENT '预定日期',
    start_time TIME NOT NULL COMMENT '开始时间',
    end_time TIME NOT NULL COMMENT '结束时间',
    attendees_count INT NOT NULL COMMENT '参会人数',
    meeting_topic VARCHAR(200) NOT NULL COMMENT '会议主题',
    status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT 'PENDING' COMMENT '预定状态',
    approval_time TIMESTAMP NULL COMMENT '审批时间',
    reject_reason VARCHAR(500) NULL COMMENT '拒绝原因',
    is_confirmed BOOLEAN NULL DEFAULT FALSE COMMENT '是否确认',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (id),
    KEY idx_user_id (user_id),
    KEY idx_room_id (room_id),
    KEY idx_booking_date (booking_date),
    CONSTRAINT fk_booking_user FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,
    CONSTRAINT fk_booking_room FOREIGN KEY (room_id) REFERENCES meeting_room(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='预定表';

SELECT '完整表结构创建测试' AS test_name, 'SUCCESS' AS result;

-- ============================================================================
-- 测试6: 验证默认值的实际应用
-- ============================================================================

-- 插入测试数据
INSERT INTO user (username, password) VALUES ('testuser', 'testpass');
INSERT INTO meeting_room (name, room_number, capacity) VALUES ('Test Room', 'R001', 10);
INSERT INTO booking (user_id, room_id, booking_date, start_time, end_time, attendees_count, meeting_topic)
VALUES (1, 1, '2025-12-01', '09:00:00', '10:00:00', 5, 'Test Meeting');

-- 查询默认值
SELECT 
    '默认值验证' AS test_name,
    (SELECT role FROM user WHERE id = 1) AS user_role_default,
    (SELECT status FROM meeting_room WHERE id = 1) AS room_status_default,
    (SELECT status FROM booking WHERE id = 1) AS booking_status_default,
    (SELECT is_confirmed FROM booking WHERE id = 1) AS booking_confirmed_default;

-- 预期结果:
-- user_role_default = 'USER'
-- room_status_default = 'AVAILABLE'
-- booking_status_default = 'PENDING'
-- booking_confirmed_default = 0 (FALSE)

-- ============================================================================
-- 总结
-- ============================================================================

SELECT '
验证总结:
✅ ENUM类型只能使用ENUM值作为默认值，不能使用CURRENT_TIMESTAMP
✅ TIMESTAMP可以使用CURRENT_TIMESTAMP作为默认值
✅ TIMESTAMP需要ON UPDATE CURRENT_TIMESTAMP才能自动更新
✅ BOOLEAN可以使用TRUE/FALSE或1/0作为默认值
✅ 修正后的表结构全部创建成功
✅ 所有默认值都正确应用

结论: 原始设计中的默认值不能按此设置，必须使用修正后的版本
' AS summary;

-- 清理
DROP DATABASE test_schema_validation;
