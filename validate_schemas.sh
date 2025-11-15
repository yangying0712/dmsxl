#!/bin/bash

# MySQL建表默认值验证脚本
# 
# 用法:
#   1. 如果你有可访问的MySQL服务器，运行: bash validate_schemas.sh
#   2. 或者在MySQL客户端中执行: mysql -u root -p < simple_validation.sql
#
# 本脚本验证:
#   - ENUM类型不能使用CURRENT_TIMESTAMP作为默认值
#   - 修正后的SQL可以成功创建所有表
#   - 所有默认值都能正确应用

echo "================================"
echo "MySQL建表默认值验证脚本"
echo "================================"
echo ""
echo "请运行以下命令以测试SQL脚本:"
echo ""
echo "  mysql -u root -p < simple_validation.sql"
echo ""
echo "或者如果你有本地MySQL服务器，可以直接执行:"
echo ""
echo "  mysql -u root -p -e 'source simple_validation.sql'"
echo ""
echo "================================"
echo ""
echo "验证内容:"
echo "  ✓ ENUM类型不能使用CURRENT_TIMESTAMP"
echo "  ✓ 修正后的表结构可以成功创建"
echo "  ✓ 所有默认值正确应用"
echo "  ✓ TIMESTAMP自动更新功能正常"
echo ""
echo "================================"
echo ""
echo "快速测试（使用simple_validation.sql）:"
echo ""

# 检查是否可以连接到MySQL
if command -v mysql &> /dev/null; then
    echo "✓ 检测到MySQL客户端"
    echo ""
    echo "尝试连接本地MySQL（如果配置了无密码访问）..."
    
    if mysql -e "SELECT 1" &> /dev/null; then
        echo "✓ 可以连接到MySQL"
        echo ""
        echo "执行验证脚本..."
        mysql < simple_validation.sql
        echo ""
        echo "✅ 验证完成！"
    else
        echo "⚠  无法连接到MySQL（可能需要密码或服务未运行）"
        echo ""
        echo "请手动运行: mysql -u root -p < simple_validation.sql"
    fi
else
    echo "⚠  未检测到MySQL客户端"
    echo ""
    echo "请安装MySQL客户端后运行: mysql -u root -p < simple_validation.sql"
fi

echo ""
echo "================================"
echo "重要结论"
echo "================================"
echo "原始设计的关键错误:"
echo "  ❌ booking.status ENUM(...) DEFAULT CURRENT_TIMESTAMP"
echo ""
echo "正确的设计:"
echo "  ✅ booking.status ENUM(...) DEFAULT 'PENDING'"
echo ""
echo "详细分析请查看:"
echo "  - SUMMARY.md (快速总结)"
echo "  - README_DATABASE.md (详细文档)"
echo "  - schema_corrected.sql (修正后的SQL)"
echo "================================"
