# MySQL建表默认值分析 - 文档索引

## 📋 快速导航

### 🚀 快速开始
1. 阅读 **[SUMMARY.md](SUMMARY.md)** - 3分钟了解核心问题
2. 使用 **[schema_corrected.sql](schema_corrected.sql)** - 直接使用修正后的SQL

### 📚 详细文档

#### 中文文档
- **[SUMMARY.md](SUMMARY.md)** - 问题总结和快速参考
- **[database_schema_analysis.md](database_schema_analysis.md)** - 详细的错误分析
- **[错误对比.md](错误对比.md)** - 错误和正确代码的对比展示

#### English Documentation
- **[README_DATABASE.md](README_DATABASE.md)** - Comprehensive analysis and guide

### 💾 SQL文件

#### 主要文件
- **[schema_corrected.sql](schema_corrected.sql)** ✅ - 修正后的表结构（推荐使用）
- **[schema_original.sql](schema_original.sql)** ❌ - 原始错误的表结构（仅供参考）

#### 测试文件
- **[simple_validation.sql](simple_validation.sql)** - 完整的验证测试脚本
- **[test_default_values.sql](test_default_values.sql)** - 默认值规则演示
- **[validate_schemas.sh](validate_schemas.sh)** - 验证脚本执行器

---

## ❌ 核心问题

原始设计中的 **booking.status** 字段使用了错误的默认值：

```sql
-- ❌ 错误 - 会导致SQL执行失败
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') 
    DEFAULT CURRENT_TIMESTAMP
```

**错误原因：**
- ENUM类型只能使用ENUM值列表中的值作为默认值
- CURRENT_TIMESTAMP是时间戳函数，类型不匹配
- MySQL会报错：`ERROR 1067 (42000): Invalid default value for 'status'`

**✅ 正确写法：**
```sql
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') 
    DEFAULT 'PENDING'
```

---

## 📊 错误统计

| 严重程度 | 数量 | 说明 |
|---------|-----|------|
| 🔴 严重 | 1 | 导致建表失败 |
| 🟡 中等 | 4 | 影响功能或导致SQL失败 |
| 🟢 轻微 | 5 | 不影响功能但降低代码质量 |

---

## 📖 使用指南

### 方案1: 直接使用修正后的SQL
```bash
mysql -u root -p < schema_corrected.sql
```

### 方案2: 修改现有错误的表
```sql
-- 修正booking.status的默认值
ALTER TABLE booking MODIFY COLUMN status 
    ENUM('PENDING','APPROVED','REJECTED','CANCELLED') 
    NULL DEFAULT 'PENDING' 
    COMMENT '预定状态';

-- 修正meeting_room.updated_at（添加自动更新）
ALTER TABLE meeting_room MODIFY COLUMN updated_at 
    TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP 
    ON UPDATE CURRENT_TIMESTAMP 
    COMMENT '更新时间';
```

### 方案3: 运行验证测试
```bash
# 运行完整验证
mysql -u root -p < simple_validation.sql

# 或使用辅助脚本
bash validate_schemas.sh
```

---

## 🔍 所有错误详情

### 1️⃣ booking.status - 🔴 严重错误
- **原始**: `DEFAULT CURRENT_TIMESTAMP`
- **修正**: `DEFAULT 'PENDING'`
- **影响**: 导致建表失败

### 2️⃣ user.password - 🟡 数据类型错误
- **原始**: `VARCGAR(255)`
- **修正**: `VARCHAR(255)`
- **影响**: SQL语法错误

### 3️⃣ meeting_room.room_number - 🟡 数据类型错误
- **原始**: `VARCGAR(50)`
- **修正**: `VARCHAR(50)`
- **影响**: SQL语法错误

### 4️⃣ meeting_room.area - 🟡 数据类型错误
- **原始**: `VDECIMAL(10,2)`
- **修正**: `DECIMAL(10,2)`
- **影响**: SQL语法错误

### 5️⃣ meeting_room.updated_at - 🟡 功能缺失
- **原始**: `DEFAULT CURRENT_TIMESTAMP`
- **修正**: `DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP`
- **影响**: 时间戳不会自动更新

### 6️⃣ 字段命名不规范 - 🟢 代码质量问题
- `Real_name` → `real_name`
- `Create_at` → `created_at`
- `updata_at` → `updated_at`
- `booking_data` → `booking_date`
- `attendess_count` → `attendees_count`

---

## 📝 MySQL默认值规则速查表

| 数据类型 | ✅ 可用默认值 | ❌ 不可用默认值 |
|---------|-------------|---------------|
| **ENUM** | ENUM值列表中的值 | 函数、其他类型值 |
| **TIMESTAMP** | CURRENT_TIMESTAMP、NOW() | ENUM值 |
| **BOOLEAN** | TRUE、FALSE、1、0 | 字符串'true'、'false' |
| **VARCHAR** | 字符串字面量 | 未加引号的值（NULL除外） |
| **INT** | 数值字面量 | 字符串、函数 |
| **DECIMAL** | 数值字面量 | 字符串、函数 |

---

## 🎯 建议行动

1. **立即修复** booking.status的默认值错误（否则无法建表）
2. **修正** 所有数据类型拼写错误
3. **添加** meeting_room.updated_at的ON UPDATE子句
4. **规范** 字段命名（建议但非必须）
5. **添加** 外键约束（建议但非必须，已在schema_corrected.sql中提供）

---

## 📞 技术支持

如有疑问，请参考：
- MySQL官方文档：https://dev.mysql.com/doc/
- ENUM类型文档：https://dev.mysql.com/doc/refman/8.0/en/enum.html
- TIMESTAMP文档：https://dev.mysql.com/doc/refman/8.0/en/datetime.html

---

## 📄 文件清单

### 文档文件
- `INDEX.md` (本文件) - 文档导航索引
- `SUMMARY.md` - 问题总结
- `README_DATABASE.md` - 详细文档（英文）
- `database_schema_analysis.md` - 详细分析（中文）
- `错误对比.md` - 错误对比（中文）

### SQL文件
- `schema_corrected.sql` - ✅ 修正后的SQL（推荐）
- `schema_original.sql` - ❌ 原始SQL（参考）
- `simple_validation.sql` - 验证测试
- `test_default_values.sql` - 规则演示

### 脚本文件
- `validate_schemas.sh` - 验证执行器

**总计：** 9个文件，约35KB

---

**版本：** 1.0  
**更新日期：** 2025-11-15  
**状态：** ✅ 已完成
