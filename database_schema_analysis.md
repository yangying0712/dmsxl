# MySQL建表默认值分析

## 问题分析

在提供的三个表的定义中，存在多个默认值设置错误和数据类型拼写错误的问题：

### 1. user表的问题

| 问题字段 | 错误 | 正确写法 | 说明 |
|---------|------|---------|------|
| password | `VARCGAR(255)` | `VARCHAR(255)` | 数据类型拼写错误 |
| Real_name | 命名不一致 | `real_name` | 应使用小写+下划线命名规范 |
| Create_at | 命名不一致 | `created_at` | 应使用小写+下划线命名规范，且通常用created_at |

**默认值分析：**
- ✅ `role ENUM('USER','ADMIN') DEFAULT 'USER'` - 正确，ENUM类型可以设置ENUM值作为默认值
- ✅ `Create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP` - 正确，TIMESTAMP可以使用CURRENT_TIMESTAMP作为默认值

### 2. meeting_room表的问题

| 问题字段 | 错误 | 正确写法 | 说明 |
|---------|------|---------|------|
| room_number | `VARCGAR(50)` | `VARCHAR(50)` | 数据类型拼写错误 |
| area | `VDECIMAL(10,2)` | `DECIMAL(10,2)` | 数据类型拼写错误 |
| updata_at | `updata_at` | `updated_at` | 字段名拼写错误 |
| updata_at | 缺少ON UPDATE子句 | 需要添加`ON UPDATE CURRENT_TIMESTAMP` | 自动更新需要明确指定 |

**默认值分析：**
- ✅ `status ENUM('AVAILABLE','UNAVAILABLE') DEFAULT 'AVAILABLE'` - 正确
- ✅ `create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP` - 正确
- ❌ `updata_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP` - 不完整，应该是：
  ```sql
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
  ```

### 3. booking表的问题

| 问题字段 | 错误 | 正确写法 | 说明 |
|---------|------|---------|------|
| booking_data | `booking_data` | `booking_date` | 字段名拼写错误（data应为date）|
| attendess_count | `attendess_count` | `attendees_count` | 字段名拼写错误 |
| status | `DEFAULT CURRENT_TIMESTAMP` | `DEFAULT 'PENDING'` | **严重错误！ENUM类型不能使用TIMESTAMP作为默认值** |

**默认值分析：**
- ❌ **`status ENUM(...) DEFAULT CURRENT_TIMESTAMP`** - **这是最严重的错误！**
  - ENUM类型只能使用ENUM定义中的值作为默认值
  - CURRENT_TIMESTAMP是时间戳函数，不能用于ENUM类型
  - 正确写法应该是：`status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') DEFAULT 'PENDING'`
  
- ✅ `is_confirmed BOOLEAN DEFAULT FALSE` - 正确，BOOLEAN（TINYINT(1)）可以使用FALSE(0)或TRUE(1)作为默认值
- ✅ `create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP` - 正确

## 总结

### MySQL默认值规则：

1. **ENUM类型**：只能使用ENUM定义中列出的值作为默认值，不能使用函数或其他类型的值
2. **TIMESTAMP类型**：可以使用`CURRENT_TIMESTAMP`、`NOW()`等时间函数作为默认值
3. **BOOLEAN类型**：可以使用`TRUE`/`FALSE`、`1`/`0`作为默认值
4. **字符串类型**：可以使用字符串字面量作为默认值
5. **数值类型**：可以使用数值字面量作为默认值

### 必须修正的错误：

1. ❌ **booking表的status字段** - 将`DEFAULT CURRENT_TIMESTAMP`改为`DEFAULT 'PENDING'`
2. ⚠️ **meeting_room表的updated_at字段** - 添加`ON UPDATE CURRENT_TIMESTAMP`以实现自动更新
3. ⚠️ 所有数据类型拼写错误（VARCGAR、VDECIMAL）
4. ⚠️ 字段命名不规范（大小写混用）

### 可选改进：

- 统一字段命名规范（全部使用小写+下划线）
- `create_at`建议改为`created_at`（更符合英语语法习惯）
- 添加外键约束（booking表的user_id和room_id）
- 添加索引优化查询性能
