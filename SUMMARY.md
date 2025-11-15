# MySQL建表默认值分析总结

## 核心问题回答

**问题：分析mysql建表，默认值是否真的能按此设置？**

**答案：❌ 不能！存在严重错误。**

## 最关键的错误

### booking表的status字段

**❌ 错误定义：**
```sql
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT CURRENT_TIMESTAMP
```

**问题说明：**
- ENUM类型字段只能使用ENUM值列表中的值作为默认值
- `CURRENT_TIMESTAMP` 是时间戳函数，返回的是时间类型
- 这个定义会导致MySQL报错：`ERROR 1067 (42000): Invalid default value for 'status'`
- **这个表无法创建成功！**

**✅ 正确定义：**
```sql
status ENUM('PENDING','APPROVED','REJECTED','CANCELLED') NULL DEFAULT 'PENDING'
```

## 其他需要修正的错误

### 1. 数据类型拼写错误（会导致SQL失败）
- `VARCGAR` → `VARCHAR`（出现2次）
- `VDECIMAL` → `DECIMAL`（出现1次）

### 2. 自动更新时间戳配置不完整（影响功能）
```sql
-- ❌ 错误：只有默认值，不会自动更新
updata_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP

-- ✅ 正确：添加ON UPDATE子句才能自动更新
updated_at TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
```

### 3. 字段命名问题（不影响功能但降低代码质量）
- `Real_name` → `real_name`
- `Create_at` → `created_at`
- `updata_at` → `updated_at`
- `booking_data` → `booking_date`
- `attendess_count` → `attendees_count`

## MySQL默认值使用规则

| 数据类型 | 可用的默认值 | 不可用的默认值 |
|---------|-------------|---------------|
| ENUM | ENUM值列表中的值<br>例：`'USER'`, `'PENDING'` | 函数、其他类型的值<br>例：`CURRENT_TIMESTAMP`, `0` |
| TIMESTAMP | `CURRENT_TIMESTAMP`, `NOW()`<br>时间字符串 | ENUM值、数字（除非是时间格式） |
| BOOLEAN | `TRUE`, `FALSE`, `1`, `0` | 字符串 `'true'`, `'false'` |
| VARCHAR | 字符串字面量<br>例：`'Unknown'`, `''` | 未加引号的值（NULL除外） |
| INT/BIGINT | 数值字面量<br>例：`0`, `100` | 字符串、函数 |
| DECIMAL | 数值字面量<br>例：`0.00`, `99.99` | 字符串、函数 |

## 文件说明

1. **schema_original.sql** - 原始错误的表结构（标注了所有问题）
2. **schema_corrected.sql** - ✅ 修正后可用的表结构
3. **README_DATABASE.md** - 详细的问题说明和修复方案（英文）
4. **database_schema_analysis.md** - 详细的错误分析（中文）
5. **错误对比.md** - 错误和正确代码的对比展示（中文）
6. **test_default_values.sql** - MySQL默认值测试脚本

## 建议

1. **立即采用** `schema_corrected.sql` 中的表结构
2. 如果已经使用错误的SQL创建了表，需要执行以下修正：

```sql
-- 修正booking表的status字段默认值
ALTER TABLE booking MODIFY COLUMN status 
    ENUM('PENDING','APPROVED','REJECTED','CANCELLED') 
    NULL DEFAULT 'PENDING' 
    COMMENT '预定状态';

-- 修正meeting_room表的updated_at字段（添加自动更新）
ALTER TABLE meeting_room MODIFY COLUMN updated_at 
    TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP 
    ON UPDATE CURRENT_TIMESTAMP 
    COMMENT '更新时间';
```

## 结论

原始设计中的默认值设置存在**严重错误**，特别是booking.status字段会导致建表失败。必须按照`schema_corrected.sql`中的定义进行修正。
