-- 修正后的表结构定义

-- 1. user表（已修正所有错误）
CREATE TABLE user (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '用户id',
    username VARCHAR(50) NOT NULL COMMENT '用户名',
    password VARCHAR(255) NOT NULL COMMENT '密码',  -- 修正：VARCGAR -> VARCHAR
    real_name VARCHAR(50) NULL COMMENT '真实姓名',  -- 修正：Real_name -> real_name
    phone VARCHAR(20) NULL COMMENT '手机号',
    email VARCHAR(100) NULL COMMENT '邮箱',
    role ENUM('USER','ADMIN') NULL DEFAULT 'USER' COMMENT '角色',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',  -- 修正：Create_at -> created_at
    PRIMARY KEY (id),
    UNIQUE KEY uk_username (username)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';

-- 2. meeting_room表（已修正所有错误）
CREATE TABLE meeting_room (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '会议室ID',
    name VARCHAR(100) NOT NULL COMMENT '会议室名称',
    room_number VARCHAR(50) NOT NULL COMMENT '房间号',  -- 修正：VARCGAR -> VARCHAR
    capacity INT NOT NULL COMMENT '容纳人数',
    area DECIMAL(10,2) NULL COMMENT '面积',  -- 修正：VDECIMAL -> DECIMAL
    purpose VARCHAR(200) NULL COMMENT '用途描述',
    photo_url VARCHAR(500) NULL COMMENT '图片',
    status ENUM('AVAILABLE','UNAVAILABLE') NULL DEFAULT 'AVAILABLE' COMMENT '状态',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',  -- 修正：create_at -> created_at
    updated_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',  -- 修正：添加ON UPDATE子句，updata_at -> updated_at
    PRIMARY KEY (id),
    UNIQUE KEY uk_room_number (room_number)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='会议室表';

-- 3. booking表（已修正所有错误）
CREATE TABLE booking (
    id BIGINT NOT NULL AUTO_INCREMENT COMMENT '预定ID',
    user_id BIGINT NOT NULL COMMENT '用户ID',
    room_id BIGINT NOT NULL COMMENT '会议室ID',
    booking_date DATE NOT NULL COMMENT '预定日期',  -- 修正：booking_data -> booking_date
    start_time TIME NOT NULL COMMENT '开始时间',
    end_time TIME NOT NULL COMMENT '结束时间',
    attendees_count INT NOT NULL COMMENT '参会人数',  -- 修正：attendess_count -> attendees_count
    meeting_topic VARCHAR(200) NOT NULL COMMENT '会议主题',
    status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT 'PENDING' COMMENT '预定状态',  -- 修正：CURRENT_TIMESTAMP -> 'PENDING'（最严重的错误）
    approval_time TIMESTAMP NULL COMMENT '审批时间',  -- 修正：审判时间 -> 审批时间
    reject_reason VARCHAR(500) NULL COMMENT '拒绝原因',
    is_confirmed BOOLEAN NULL DEFAULT FALSE COMMENT '是否确认',
    created_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',  -- 修正：create_at -> created_at
    PRIMARY KEY (id),
    KEY idx_user_id (user_id),
    KEY idx_room_id (room_id),
    KEY idx_booking_date (booking_date),  -- 修正：索引字段名
    CONSTRAINT fk_booking_user FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,  -- 添加：外键约束
    CONSTRAINT fk_booking_room FOREIGN KEY (room_id) REFERENCES meeting_room(id) ON DELETE CASCADE  -- 添加：外键约束
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='预定表';
