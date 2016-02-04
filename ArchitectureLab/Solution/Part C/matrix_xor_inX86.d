O3

00000040 <matrix_xor>:
  40:	55                   	push   %ebp
  41:	89 e5                	mov    %esp,%ebp
  43:	57                   	push   %edi
  44:	56                   	push   %esi
  45:	53                   	push   %ebx
  46:	83 ec 14             	sub    $0x14,%esp
  49:	8b 75 08             	mov    0x8(%ebp),%esi

  4c:	85 f6                	test   %esi,%esi
  4e:	7e 7b                	jle    cb <matrix_xor+0x8b>

  50:	8d 04 b5 00 00 00 00 	lea    0x0(,%esi,4),%eax

  57:	89 45 f0             	mov    %eax,-0x10(%ebp)
  5a:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
  61:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%ebp)

  68:	8b 45 14             	mov    0x14(%ebp),%eax
  6b:	8b 7d 0c             	mov    0xc(%ebp),%edi
  6e:	03 45 e4             	add    -0x1c(%ebp),%eax

  71:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
  78:	8b 55 ec             	mov    -0x14(%ebp),%edx
  7b:	03 7d e4             	add    -0x1c(%ebp),%edi
  
  7e:	89 45 e8             	mov    %eax,-0x18(%ebp)
  81:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  88:	8b 45 10             	mov    0x10(%ebp),%eax
  8b:	31 db                	xor    %ebx,%ebx
  8d:	8d 0c 90             	lea    (%eax,%edx,4),%ecx
  90:	31 c0                	xor    %eax,%eax
  92:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  98:	8b 11                	mov    (%ecx),%edx
  9a:	33 14 87             	xor    (%edi,%eax,4),%edx
  9d:	83 c0 01             	add    $0x1,%eax
  a0:	03 4d f0             	add    -0x10(%ebp),%ecx
  a3:	01 d3                	add    %edx,%ebx
  a5:	39 f0                	cmp    %esi,%eax
  a7:	75 ef                	jne    98 <matrix_xor+0x58>

  a9:	8b 55 ec             	mov    -0x14(%ebp),%edx
  ac:	8b 45 e8             	mov    -0x18(%ebp),%eax
  af:	89 1c 90             	mov    %ebx,(%eax,%edx,4)
  b2:	83 c2 01             	add    $0x1,%edx
  b5:	39 f2                	cmp    %esi,%edx
  b7:	89 55 ec             	mov    %edx,-0x14(%ebp)
  ba:	75 cc                	jne    88 <matrix_xor+0x48>

  bc:	83 45 e0 01          	addl   $0x1,-0x20(%ebp)
  c0:	8b 55 f0             	mov    -0x10(%ebp),%edx
  c3:	01 55 e4             	add    %edx,-0x1c(%ebp)
  c6:	39 75 e0             	cmp    %esi,-0x20(%ebp)
  c9:	75 9d                	jne    68 <matrix_xor+0x28>

  cb:	83 c4 14             	add    $0x14,%esp
  ce:	5b                   	pop    %ebx
  cf:	5e                   	pop    %esi
  d0:	5f                   	pop    %edi
  d1:	5d                   	pop    %ebp
  d2:	c3                   	ret    
