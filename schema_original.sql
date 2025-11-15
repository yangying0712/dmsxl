-- 原始表结构定义（存在错误）

-- 1. user表（存在拼写和命名错误）
CREATE TABLE user (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '用户id',
    username VARCHAR(50) NOT NULL COMMENT '用户名',
    password VARCGAR(255) NOT NULL COMMENT '密码',  -- 错误：VARCGAR应为VARCHAR
    Real_name VARCHAR(50) NULL COMMENT '真实姓名',  -- 错误：命名不规范
    phone VARCHAR(20) NULL COMMENT '手机号',
    email VARCHAR(100) NULL COMMENT '邮箱',
    role ENUM('USER','ADMIN') NULL DEFAULT 'USER' COMMENT '角色',
    Create_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',  -- 错误：命名不规范
    PRIMARY KEY (id),
    UNIQUE KEY uk_username (username)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';

-- 2. meeting_room表（存在拼写错误和缺少ON UPDATE子句）
CREATE TABLE meeting_room (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '会议室ID',
    name VARCHAR(100) NOT NULL COMMENT '会议室名称',
    room_number VARCGAR(50) NOT NULL COMMENT '房间号',  -- 错误：VARCGAR应为VARCHAR
    capacity INT NOT NULL COMMENT '容纳人数',
    area VDECIMAL(10,2) NULL COMMENT '面积',  -- 错误：VDECIMAL应为DECIMAL
    purpose VARCHAR(200) NULL COMMENT '用途描述',
    photo_url VARCHAR(500) NULL COMMENT '图片',
    status ENUM('AVAILABLE','UNAVAILABLE') NULL DEFAULT 'AVAILABLE' COMMENT '状态',
    create_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    updata_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '更新时间',  -- 错误：缺少ON UPDATE CURRENT_TIMESTAMP，且拼写错误
    PRIMARY KEY (id),
    UNIQUE KEY uk_room_number (room_number)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='会议室表';

-- 3. booking表（存在严重的默认值错误）
CREATE TABLE booking (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '预定ID',
    user_id BIGINT NOT NULL COMMENT '用户ID',
    room_id BIGINT NOT NULL COMMENT '会议室ID',
    booking_data DATE NOT NULL COMMENT '预定日期',  -- 错误：booking_data应为booking_date
    start_time TIME NOT NULL COMMENT '开始时间',
    end_time TIME NOT NULL COMMENT '结束时间',
    attendess_count INT NOT NULL COMMENT '参会人数',  -- 错误：attendess_count应为attendees_count
    meeting_topic VARCHAR(200) NOT NULL COMMENT '会议主题',
    status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT CURRENT_TIMESTAMP COMMENT '预定状态',  -- 严重错误：ENUM不能使用CURRENT_TIMESTAMP作为默认值
    approval_time TIMESTAMP NULL COMMENT '审判时间',
    reject_reason VARCHAR(500) NULL COMMENT '拒绝原因',
    is_confirmed BOOLEAN NULL DEFAULT FALSE COMMENT '是否确认',
    create_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (id),
    KEY idx_user_id (user_id),
    KEY idx_room_id (room_id),
    KEY idx_booking_date (booking_data)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='预定表';
