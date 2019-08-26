import java.awt.*;
import java.awt.Window.Type;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.math.BigDecimal;
import java.text.*;
import javax.swing.*;


public class Calculator {


	private JFrame frmJavav;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Calculator window = new Calculator();
					window.frmJavav.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Calculator() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	public class newans {
		private double ans = 0,num=0;
		private long operation = 0, decimal = 0,ifequals=0,equals=0;
		

		public String formatDecimal(double d, long newScale) {
			String pattern = "#.";
			for (long i = 0; i < newScale; i++) {
				pattern += "0";
			}
			DecimalFormat df = new DecimalFormat(pattern);
			return df.format(d);
		}

		public newans() {

		}
		




		public long getIfequals() {
			return ifequals;
		}

		public void setIfequals(long ifequals) {
			this.ifequals = ifequals;
		}

		public double getNum() {
			return num;
		}

		public void setNum(double num) {
			this.num = num;
		}


		public void setEuqals(long equ){
			equals=equ;
		}
		public long getEquals(){
			return equals;
		}
		public void setAns(double num) {
			ans = num;
		}

		public double getAns() {
			return ans;
		}

		public void setOperation(long op) {
			operation = op;
		}

		public long getOperation() {
			return operation;
		}

		public void setDecimal(long xs) {
			decimal = xs;
		}

		public long getDecimal() {
			return decimal;
		}

	

	}

	private void initialize() {

		Dimension ScreenSize=Toolkit.getDefaultToolkit().getScreenSize();
		double scrh=ScreenSize.getHeight(),scrw=ScreenSize.getWidth();
		int frameh=307,framew=450;
		
		newans ans = new newans();

		frmJavav = new JFrame();
		frmJavav.setType(Type.UTILITY);
		frmJavav.setTitle("计算器");
		frmJavav.setResizable(false);
		frmJavav.setBounds((int)(scrw-framew)/2,(int)(scrh-frameh)/2 , frameh, framew);
		frmJavav.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel panel = new JPanel();
		frmJavav.getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);
		
		JPanel panel2 = new JPanel();
		panel2.setLayout(null);
		
		JMenuBar bar=new JMenuBar();
		frmJavav.setJMenuBar(bar);
		
		JMenu caidan=new JMenu("菜单");
		bar.add(caidan);
		
		JMenuItem ctfg=new JMenuItem("窗体风格");
		caidan.add(ctfg);
		ctfg.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				Object[] possibleValues = { "NORMAL", "UTILITY", "POPUP" }; //用户的选择项目
				Object selectedValue = JOptionPane.showInputDialog(frmJavav, "选择你需要的窗体风格", "窗体风格选择",JOptionPane.INFORMATION_MESSAGE, null, possibleValues, possibleValues[0]);
				frmJavav.remove(panel);	
				frmJavav.setContentPane(panel2);
			}	
		});
		
		JMenuItem exit=new JMenuItem("退出");
		caidan.add(exit);
		exit.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				long xz=JOptionPane.showConfirmDialog(frmJavav, "要退出扫雷吗?","确定退出",JOptionPane.YES_NO_OPTION);
				if(xz==0)
					System.exit(0);
			}		
		});
		
		JMenu bangzhu =new JMenu("帮助");
		bar.add(bangzhu);
		
		
		JMenuItem gy=new JMenuItem("关于");
		bangzhu.add(gy);
		gy.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				JOptionPane.showMessageDialog(frmJavav, "软件名：计算器\n制作时间：2017年4月16日\n制作人：兰州大学2016级计算机2班 俞挺挺","版权信息",JOptionPane.PLAIN_MESSAGE);
			}
		});
	
		class MyPanel extends JPanel
		{
		   public void palong(Graphics g){
		     g.drawLine(10, 10, 50, 50);
		   }
		}
		
		MyPanel pan1=new MyPanel();

		panel.add(pan1);

		JLabel lblNewLabel = new JLabel("0");
		lblNewLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		lblNewLabel.setBounds(50, 20, 200, 50);
		panel.add(lblNewLabel);

		JButton btnNewButton = new JButton("7");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {


				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 7);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 7.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 7);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 7.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

			}
		});
		btnNewButton.setBackground(Color.LIGHT_GRAY);
		btnNewButton.setBounds(50, 120, 50, 50);
		panel.add(btnNewButton);

		JButton btnNewButton_1 = new JButton("8");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 8);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 8.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 8);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 8.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

			}
		});
		btnNewButton_1.setBackground(Color.LIGHT_GRAY);
		btnNewButton_1.setBounds(100, 120, 50, 50);
		panel.add(btnNewButton_1);

		JButton button = new JButton("9");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 9);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 9.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 9);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 9.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}
			}
		});
		button.setBackground(Color.LIGHT_GRAY);
		button.setBounds(150, 120, 50, 50);
		panel.add(button);

		JButton button_1 = new JButton("4");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 4);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 4.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 4);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 4.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

				
			}
		});
		button_1.setBackground(Color.LIGHT_GRAY);
		button_1.setBounds(50, 170, 50, 50);
		panel.add(button_1);

		JButton button_2 = new JButton("5");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 5);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 5.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 5);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 5.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

			}
		});
		button_2.setBackground(Color.LIGHT_GRAY);
		button_2.setBounds(100, 170, 50, 50);
		panel.add(button_2);

		JButton button_3 = new JButton("6");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 6);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 6.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 6);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 6.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

			}
		});
		button_3.setBackground(Color.LIGHT_GRAY);
		button_3.setBounds(150, 170, 50, 50);
		panel.add(button_3);

		JButton button_4 = new JButton("1");
		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {

				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 1);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 1.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 1);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 1.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}

				
				
			}
		});
		button_4.setBackground(Color.LIGHT_GRAY);
		button_4.setBounds(50, 220, 50, 50);
		panel.add(button_4);

		JButton button_5 = new JButton("2");
		button_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {


				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 2);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 2.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 2);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 2.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}
				

			}
		});
		button_5.setBackground(Color.LIGHT_GRAY);
		button_5.setBounds(100, 220, 50, 50);
		panel.add(button_5);

		JButton button_6 = new JButton("3");
		button_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {


				if (ans.getOperation() != 0) {
					if (ans.getDecimal() == 0) {
						ans.setNum(ans.getNum() * 10 + 3);
						lblNewLabel.setText("" + (long) ans.getNum());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setNum(Double.valueOf(ans.formatDecimal(
									ans.getNum() + 3.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getNum());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getNum());
						}
					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setAns(ans.getAns() * 10 + 3);
						lblNewLabel.setText("" + (long) ans.getAns());
					} else {
						if (ans.getDecimal() < 16) {
							ans.setAns(Double.valueOf(ans.formatDecimal(
									ans.getAns() + 3.0 / Math.pow(10, ans.getDecimal()), ans.getDecimal())));
							lblNewLabel.setText("" + ans.getAns());
							ans.setDecimal(ans.getDecimal() + 1);
						} else {
							lblNewLabel.setText("" + ans.getAns());
						}
					}
				}
				

			}
		});
		button_6.setBackground(Color.LIGHT_GRAY);
		button_6.setBounds(150, 220, 50, 50);
		panel.add(button_6);

		JButton button_7 = new JButton("0");
		button_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				if (ans.getOperation() == 0) {
					if (ans.getDecimal() == 0) {
						ans.setAns(0);
					} else {
						if (ans.getAns() != 0) {
							ans.setDecimal(ans.getDecimal() + 1);
							if (Math.round(ans.getAns()) != 0)
								lblNewLabel.setText(ans.formatDecimal(ans.getAns(), ans.getDecimal() - 1));
							else
								lblNewLabel.setText("0" + ans.formatDecimal(ans.getAns(), ans.getDecimal() - 1));
						} else {
							lblNewLabel.setText("0.");
						}

					}
				} else {
					if (ans.getDecimal() == 0) {
						ans.setNum(0);
						lblNewLabel.setText("0");
					} else {
						if (ans.getNum() != 0) {
							ans.setDecimal(ans.getDecimal() + 1);
							if (Math.round(ans.getNum()) != 0)
								lblNewLabel.setText(ans.formatDecimal(ans.getNum(), ans.getDecimal() - 1));
							else
								lblNewLabel.setText("0" + ans.formatDecimal(ans.getNum(), ans.getDecimal() - 1));
						} else {
							lblNewLabel.setText("0.");
						}

					}
				}
				
				
				
			}
		});
		button_7.setBackground(Color.LIGHT_GRAY);
		button_7.setBounds(50, 270, 100, 50);
		panel.add(button_7);

		JButton button_8 = new JButton(".");
		button_8.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {

				ans.setDecimal(1);
				if(ans.getEquals()!=0)
				{
					ans.setEuqals(0);
					ans.setOperation(3);
					ans.setNum(0);
					ans.setIfequals(0);
					if (ans.getNum() != 0) {
						ans.setDecimal(ans.getDecimal() + 1);
						if (Math.round(ans.getNum()) != 0)
							lblNewLabel.setText(ans.formatDecimal(ans.getNum(), ans.getDecimal() - 1));
						else
							lblNewLabel.setText("0" + ans.formatDecimal(ans.getNum(), ans.getDecimal() - 1));
					} else {
						lblNewLabel.setText("0.");
					}
				}
				else{
					if (ans.getOperation() == 0)
						lblNewLabel.setText("" + (long) ans.getAns() + ".");
					else
						lblNewLabel.setText("" + (long) ans.getNum() + ".");
				}
				

			}
		});
		button_8.setBackground(Color.LIGHT_GRAY);
		button_8.setBounds(150, 270, 50, 50);
		panel.add(button_8);

		JButton btnAc = new JButton("AC");
		btnAc.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setAns(0);
				ans.setDecimal(0);
				ans.setEuqals(0);
				ans.setOperation(0);
				ans.setNum(0);
				lblNewLabel.setText("0");
				ans.setIfequals(0);
			}
		});
		btnAc.setBackground(Color.LIGHT_GRAY);
		btnAc.setBounds(50, 70, 50, 50);
		panel.add(btnAc);

		JButton button_10 = new JButton("+/-");
		button_10.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setAns(-ans.getAns());
				ans.setOperation(0);
			}
		});
		button_10.setBackground(Color.LIGHT_GRAY);
		button_10.setFont(new Font("宋体", Font.PLAIN, 10));
		button_10.setBounds(100, 70, 50, 50);
		panel.add(button_10);

		JButton button_11 = new JButton("%");
		button_11.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setAns(BigDecimal.valueOf(ans.getAns()).divide(BigDecimal.valueOf(100)).doubleValue());
				ans.setOperation(0);
			}
		});
		button_11.setBackground(Color.LIGHT_GRAY);
		button_11.setBounds(150, 70, 50, 50);
		panel.add(button_11);

		JButton button_9 = new JButton("\u00F7");
		button_9.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setDecimal(0);
				ans.setNum(0);
				ans.setOperation(4);
			}
		});
		button_9.setBackground(Color.LIGHT_GRAY);
		button_9.setBounds(200, 70, 50, 50);
		panel.add(button_9);

		JButton button_12 = new JButton("\u00D7");
		button_12.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setDecimal(0);
				ans.setNum(0);
				ans.setOperation(3);
			}
		});
		button_12.setBackground(Color.LIGHT_GRAY);
		button_12.setBounds(200, 120, 50, 50);
		panel.add(button_12);

		JButton button_13 = new JButton("\u2014");
		button_13.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setDecimal(0);
				ans.setNum(0);
				ans.setOperation(2);
			}
		});
		button_13.setBackground(Color.LIGHT_GRAY);
		button_13.setBounds(200, 170, 50, 50);
		panel.add(button_13);

		JButton button_14 = new JButton("+");
		button_14.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setDecimal(0);
				ans.setNum(0);
				ans.setOperation(1);
			}
		});
		button_14.setBackground(Color.LIGHT_GRAY);
		button_14.setBounds(200, 220, 50, 50);
		panel.add(button_14);

		JButton button_15 = new JButton("=");
		button_15.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ans.setEuqals(1);
				// 精确计算
				switch (ans.getOperation()) {
				case 1:
					ans.setAns(BigDecimal.valueOf(ans.getAns()).add(BigDecimal.valueOf(ans.getNum())).doubleValue());
					break;
				case 2:
					ans.setAns(
							BigDecimal.valueOf(ans.getAns()).subtract(BigDecimal.valueOf(ans.getNum())).doubleValue());
					break;
				case 3:
					ans.setAns(
							BigDecimal.valueOf(ans.getAns()).multiply(BigDecimal.valueOf(ans.getNum())).doubleValue());
					break;
				case 4:{
					if(ans.getNum()==0){
						ans.setAns(0);
						ans.setDecimal(0);
						ans.setEuqals(0);
						ans.setIfequals(1);
						
					}else{
						ans.setAns(BigDecimal.valueOf(ans.getAns()).divide(BigDecimal.valueOf(ans.getNum()),16,BigDecimal.ROUND_HALF_UP).doubleValue());
					}
				};break;
				default:
					break;
				}

				if (ans.getAns() == Math.round(ans.getAns())) {
					ans.setDecimal(0);
				} else {

				}
				
				if(ans.getIfequals()!=0){
					lblNewLabel.setText("错误");
				}
				else{
					if (ans.getAns() == Math.round(ans.getAns()))
						lblNewLabel.setText("" + (long) ans.getAns());
					else
						lblNewLabel.setText("" + ans.getAns());
				}


			}
		});
		button_15.setBackground(Color.LIGHT_GRAY);
		button_15.setBounds(200, 270, 50, 50);
		panel.add(button_15);

	}
}