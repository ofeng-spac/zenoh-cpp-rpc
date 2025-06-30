# Git 常用命令参考

## 项目初始化和配置

```bash
# 初始化Git仓库
git init

# 配置用户信息
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 查看配置
git config --list
```

## 基本操作命令

### 添加和提交
```bash
# 查看文件状态
git status

# 添加所有文件到暂存区
git add .

# 添加特定文件
git add filename

# 提交更改
git commit -m "提交信息"

# 添加并提交（已跟踪文件）
git commit -am "提交信息"
```

### 查看历史
```bash
# 查看提交历史
git log

# 简洁查看历史
git log --oneline

# 查看文件差异
git diff

# 查看已暂存的差异
git diff --cached
```

## 远程仓库操作

### 连接远程仓库
```bash
# 添加远程仓库
git remote add origin https://github.com/username/repository.git

# 查看远程仓库
git remote -v

# 修改远程仓库URL
git remote set-url origin https://github.com/username/new-repository.git
```

### 推送和拉取
```bash
# 首次推送到远程仓库
git push -u origin main

# 推送到远程仓库
git push

# 推送特定分支
git push origin branch-name

# 拉取远程更新
git pull

# 获取远程更新（不合并）
git fetch
```

## 分支管理

```bash
# 查看分支
git branch

# 创建新分支
git branch new-branch

# 切换分支
git checkout branch-name

# 创建并切换到新分支
git checkout -b new-branch

# 合并分支
git merge branch-name

# 删除分支
git branch -d branch-name
```

## 标签管理

```bash
# 创建标签
git tag v1.1.0

# 创建带注释的标签
git tag -a v1.1.0 -m "版本 1.1.0"

# 查看标签
git tag

# 推送标签
git push origin v1.1.0

# 推送所有标签
git push origin --tags
```

## 项目发布流程

### 完整的项目上传流程
```bash
# 1. 初始化仓库（如果是新项目）
git init

# 2. 添加所有文件
git add .

# 3. 首次提交
git commit -m "Initial commit: v1.1.0 - 完善的错误处理和文档系统"

# 4. 添加远程仓库
git remote add origin https://github.com/username/zenoh-cpp-rpc.git

# 5. 推送到远程仓库
git push -u origin main

# 6. 创建版本标签
git tag -a v1.1.0 -m "版本 1.1.0: 完善的错误处理系统、中文文档和学习笔记"

# 7. 推送标签
git push origin v1.1.0
```

### 后续更新流程
```bash
# 1. 查看状态
git status

# 2. 添加更改
git add .

# 3. 提交更改
git commit -m "feat: 添加新功能" # 或 "fix: 修复bug" 或 "docs: 更新文档"

# 4. 推送更改
git push

# 5. 如果是新版本，创建标签
git tag -a v1.2.0 -m "版本 1.2.0: 新功能描述"
git push origin v1.2.0
```

## 常用的提交信息格式

```bash
# 功能相关
git commit -m "feat: 添加新的RPC方法"
git commit -m "feat(client): 改进客户端连接逻辑"

# 修复相关
git commit -m "fix: 修复内存泄漏问题"
git commit -m "fix(server): 修复服务器启动错误"

# 文档相关
git commit -m "docs: 更新README文档"
git commit -m "docs: 添加API使用示例"

# 重构相关
git commit -m "refactor: 重构错误处理逻辑"

# 测试相关
git commit -m "test: 添加单元测试"

# 构建相关
git commit -m "build: 更新CMakeLists.txt"
```

## 撤销和回退

```bash
# 撤销工作区的更改
git checkout -- filename

# 撤销暂存区的更改
git reset HEAD filename

# 撤销最后一次提交（保留更改）
git reset --soft HEAD~1

# 撤销最后一次提交（丢弃更改）
git reset --hard HEAD~1

# 查看引用日志
git reflog
```

## .gitignore 文件示例

```bash
# 创建 .gitignore 文件
cat > .gitignore << EOF
# 编译输出
build/
*.o
*.so
*.a
*.exe

# IDE文件
.vscode/
.idea/
*.swp
*.swo

# 系统文件
.DS_Store
Thumbs.db

# 临时文件
*.tmp
*.log
EOF
```

## 常见问题解决

### 解决合并冲突
```bash
# 查看冲突文件
git status

# 手动编辑冲突文件后
git add conflicted-file
git commit -m "resolve: 解决合并冲突"
```

### 强制推送（谨慎使用）
```bash
# 强制推送（会覆盖远程历史）
git push --force-with-lease
```

### 克隆仓库
```bash
# 克隆仓库
git clone https://github.com/username/repository.git

# 克隆特定分支
git clone -b branch-name https://github.com/username/repository.git
```

---

**注意事项：**
1. 在推送前总是先检查 `git status`
2. 提交信息要清晰描述更改内容
3. 定期备份重要分支
4. 使用有意义的分支名称
5. 在团队协作时，推送前先拉取最新更改