# MySQL数据库表设计分析

## 概述

本文档分析了会议室预定系统的三个数据库表（user、meeting_room、booking）的设计问题，特别是默认值设置的错误。

## 问题背景

用户提供了三个表的设计文档，询问"默认值是否真的能按此设置"。经过分析，发现存在**多处严重错误**，其中最严重的是**booking表的status字段使用了错误的默认值类型**。

## 最严重的错误

### ❌ booking.status字段的默认值错误

**原始定义：**
```sql
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT CURRENT_TIMESTAMP
```

**问题：**
- ENUM类型的字段只能使用ENUM定义中列出的值作为默认值
- `CURRENT_TIMESTAMP`是一个返回时间戳的函数，类型不匹配
- 这会导致建表失败，MySQL会报错：`Invalid default value for 'status'`

**正确定义：**
```sql
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT 'PENDING'
```

## 其他错误汇总

### 1. 数据类型拼写错误

| 表名 | 字段 | 错误 | 正确 |
|-----|------|-----|------|
| user | password | `VARCGAR(255)` | `VARCHAR(255)` |
| meeting_room | room_number | `VARCGAR(50)` | `VARCHAR(50)` |
| meeting_room | area | `VDECIMAL(10,2)` | `DECIMAL(10,2)` |

### 2. 字段命名不规范

| 表名 | 字段 | 错误 | 正确 |
|-----|------|-----|------|
| user | Real_name | 大小写混用 | `real_name` |
| user | Create_at | 大小写混用 | `created_at` |
| meeting_room | create_at | 语法不完整 | `created_at` |
| meeting_room | updata_at | 拼写错误 | `updated_at` |
| booking | booking_data | 拼写错误 | `booking_date` |
| booking | attendess_count | 拼写错误 | `attendees_count` |
| booking | create_at | 语法不完整 | `created_at` |

### 3. 自动更新时间戳配置不完整

**原始定义：**
```sql
updata_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP
```

**问题：**
- 注释说"自动更新"，但缺少`ON UPDATE CURRENT_TIMESTAMP`子句
- 没有这个子句，时间戳不会自动更新

**正确定义：**
```sql
updated_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
```

## MySQL默认值规则

### 1. ENUM类型
- ✅ **可以**：使用ENUM定义中的任何一个值
- ❌ **不可以**：使用函数（如CURRENT_TIMESTAMP）、其他类型的值

**示例：**
```sql
role ENUM('USER','ADMIN') DEFAULT 'USER'  -- ✅ 正确
status ENUM('PENDING','APPROVED') DEFAULT CURRENT_TIMESTAMP  -- ❌ 错误
```

### 2. TIMESTAMP/DATETIME类型
- ✅ **可以**：CURRENT_TIMESTAMP、NOW()、特定时间字符串
- ✅ **可以**：ON UPDATE CURRENT_TIMESTAMP（自动更新）

**示例：**
```sql
created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP  -- ✅ 正确
updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP  -- ✅ 正确
```

### 3. BOOLEAN类型
- ✅ **可以**：TRUE、FALSE、1、0

**示例：**
```sql
is_confirmed BOOLEAN DEFAULT FALSE  -- ✅ 正确
is_active BOOLEAN DEFAULT TRUE  -- ✅ 正确
```

### 4. 字符串类型（VARCHAR、CHAR、TEXT）
- ✅ **可以**：字符串字面量（用引号包围）
- ❌ **不可以**：未加引号的值（除非是NULL）

### 5. 数值类型（INT、BIGINT、DECIMAL等）
- ✅ **可以**：数值字面量
- ❌ **不可以**：字符串或函数

## 文件说明

- `schema_original.sql` - 原始表结构（包含所有错误）
- `schema_corrected.sql` - 修正后的表结构（所有错误已修复）
- `database_schema_analysis.md` - 详细的错误分析文档
- `test_default_values.sql` - 默认值测试脚本

## 使用建议

1. **立即修复**：booking表的status字段默认值必须修改，否则无法建表
2. **规范命名**：统一使用小写+下划线的命名风格
3. **添加约束**：建议为booking表添加外键约束
4. **添加索引**：根据查询需求优化索引

## 总结

原始设计中最严重的问题是**booking.status字段使用CURRENT_TIMESTAMP作为ENUM类型的默认值**，这会导致SQL执行失败。其他问题主要是拼写错误和命名不规范，虽然不影响功能，但应该修正以提高代码质量和可维护性。

所有问题的修正版本已在`schema_corrected.sql`文件中提供。
