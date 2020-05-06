// Test bench generated by generator_verilog.py

`timescale 1 ns / 1 ps

//import global_pkg::*;

module tb_top_tf();

// Defines
`define DEBUG 1

// Simulation constants and signals /////////////////////////////////
  time    c_CLK = 4ns; // Clock periode
  integer clk_cnt = 0; // Clock counter
  string line;     // String value read from the file
  string line_sel; // Selected string value read from the file
  string FILE_IN[0:7] = {"TrackletProjections_TPROJ_L1L2H_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L5L6C_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L1L2I_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L5L6B_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L5L6D_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L1L2J_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L1L2G_L3PHIC_04MOD.dat",
                         "TrackletProjections_TPROJ_L1L2F_L3PHIC_04MOD.dat" };
  integer f_i [0:7];   // File handle
  string FILE_OUT = "../../../../../output.txt";
  integer f_o;         // File handle
  integer fgets_rtn;
// Signals to connect the DUT /////////////////
// Control signals
  logic clk     = 1'b0;
  logic reset   = 1'b0;
  logic en_proc = 1'b0;
  logic [2:0] bx_in_ProjectionRouter;
// PR inputs
  logic TPROJ_L3PHIC_dataarray_data_V_wea [7:0]             = '{default:0};
  logic [7:0] TPROJ_L3PHIC_dataarray_data_V_writeaddr [7:0] = '{default:'{default:0} };;
  logic [59:0] TPROJ_L3PHIC_dataarray_data_V_din [7:0];
  logic TPROJ_L3PHIC_nentries_V_we [0:1][7:0]               = '{default:1};
  logic [7:0] TPROJ_L3PHIC_nentries_V_din [0:1][7:0]        = { {8'b00000001, 8'b00010111, 8'b00000100, 8'b00000001, 8'b00000000, 8'b00001010, 8'b00001010, 8'b00000110},
                                                                {8'b00000000, 8'b00001111, 8'b00001111, 8'b00000100, 8'b00000000, 8'b00001011, 8'b00000010, 8'b00001000} };
                                                                   //  1, 0,     23, 15,      4, 15,       1, 4,       0, 0,     10, 11,      10, 2,       6, 8
// ME inputs
  logic VMSME_L3PHIC17to24n1_dataarray_data_V_wea [7:0];
  logic [9:0] VMSME_L3PHIC17to24n1_dataarray_data_V_writeaddr [7:0];
  logic [13:0] VMSME_L3PHIC17to24n1_dataarray_data_V_din [7:0]; 
  logic VMSME_L3PHIC17to24n1_nentries_V_we [0:7][7:0];
  logic [6:0] VMSME_L3PHIC17to24n1_nentries_V_din [0:7][7:0];
// MC inputs
  logic AS_L3PHICn4_dataarray_data_V_wea;
  logic [9:0] AS_L3PHICn4_dataarray_data_V_writeaddr;
  logic [35:0] AS_L3PHICn4_dataarray_data_V_din;
  logic AS_L3PHICn4_dataarray_nentries_V_we [0:7];
  logic [6:0] AS_L3PHICn4_dataarray_nentries_V_din [0:7];
// MC outputs
  logic FM_L1L2XX_L3PHIC_dataarray_data_V_enb            = 1'b0;
  logic [7:0] FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr = '{default:0};
  logic [44:0] FM_L1L2XX_L3PHIC_dataarray_data_V_dout;
  logic [6:0] FM_L1L2XX_L3PHIC_nentries_0_V_dout [0:1];
  logic FM_L5L6XX_L3PHIC_dataarray_data_V_enb            = 1'b0;
  logic [7:0] FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr = '{default:0};
  logic [44:0] FM_L5L6XX_L3PHIC_dataarray_data_V_dout;
  logic [6:0] FM_L5L6XX_L3PHIC_nentries_0_V_dout [0:1];
// More control signals
  logic [2:0] bx_out_MatchCalculator;
  logic MatchCalculator_done;
// Other signals ///////////


// Top module //////////////////////////////////////
top_tf top_tf_inst (
// Control signals
  .clk(clk),
  .reset(reset),
  .en_proc(en_proc),
  .bx_in_ProjectionRouter(bx_in_ProjectionRouter),
// PR inputs
  .TPROJ_L3PHIC_dataarray_data_V_wea(TPROJ_L3PHIC_dataarray_data_V_wea),
  .TPROJ_L3PHIC_dataarray_data_V_writeaddr(TPROJ_L3PHIC_dataarray_data_V_writeaddr),
  .TPROJ_L3PHIC_dataarray_data_V_din(TPROJ_L3PHIC_dataarray_data_V_din),
  .TPROJ_L3PHIC_nentries_V_we(TPROJ_L3PHIC_nentries_V_we),
  .TPROJ_L3PHIC_nentries_V_din(TPROJ_L3PHIC_nentries_V_din),
// ME inputs
  .VMSME_L3PHIC17to24n1_dataarray_data_V_wea(VMSME_L3PHIC17to24n1_dataarray_data_V_wea),
  .VMSME_L3PHIC17to24n1_dataarray_data_V_writeaddr(VMSME_L3PHIC17to24n1_dataarray_data_V_writeaddr),
  .VMSME_L3PHIC17to24n1_dataarray_data_V_din(VMSME_L3PHIC17to24n1_dataarray_data_V_din), 
  .VMSME_L3PHIC17to24n1_nentries_V_we(VMSME_L3PHIC17to24n1_nentries_V_we),
  .VMSME_L3PHIC17to24n1_nentries_V_din(VMSME_L3PHIC17to24n1_nentries_V_din),
// MC inputs
  .AS_L3PHICn4_dataarray_data_V_wea(AS_L3PHICn4_dataarray_data_V_wea),
  .AS_L3PHICn4_dataarray_data_V_writeaddr(AS_L3PHICn4_dataarray_data_V_writeaddr),
  .AS_L3PHICn4_dataarray_data_V_din(AS_L3PHICn4_dataarray_data_V_din),
  .AS_L3PHICn4_dataarray_nentries_V_we(AS_L3PHICn4_dataarray_nentries_V_we),
  .AS_L3PHICn4_dataarray_nentries_V_din(AS_L3PHICn4_dataarray_nentries_V_din),
// MC outputs
  .FM_L1L2XX_L3PHIC_dataarray_data_V_enb(FM_L1L2XX_L3PHIC_dataarray_data_V_enb),
  .FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr(FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr),
  .FM_L1L2XX_L3PHIC_dataarray_data_V_dout(FM_L1L2XX_L3PHIC_dataarray_data_V_dout),
  .FM_L1L2XX_L3PHIC_nentries_0_V_dout(FM_L1L2XX_L3PHIC_nentries_0_V_dout),
  .FM_L5L6XX_L3PHIC_dataarray_data_V_enb(FM_L5L6XX_L3PHIC_dataarray_data_V_enb),
  .FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr(FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr),
  .FM_L5L6XX_L3PHIC_dataarray_data_V_dout(FM_L5L6XX_L3PHIC_dataarray_data_V_dout),
  .FM_L5L6XX_L3PHIC_nentries_0_V_dout(FM_L5L6XX_L3PHIC_nentries_0_V_dout),
// More control signals
  .bx_out_MatchCalculator(bx_out_MatchCalculator),
  .MatchCalculator_done(MatchCalculator_done)
);


// Write output to file
initial  begin
 $dumpfile ("top_tf.vcd"); // Waveform
 $dumpvars; 
 for (int i = 0; i <= 7; i++) begin
   f_i[i] = $fopen(FILE_IN[i],"r");
 end
 f_o = $fopen(FILE_OUT,"w");
 $fwrite(f_o,"  time clk_cnt reset   enb readaddr FM_L1L2XX_L3PHIC_*_dout" ,
                               "   enb readaddr FM_L1L2XX_L3PHIC_*_dout\n");
end 

// Clock generation and file writing
always begin
  #(c_CLK/2) clk = !clk; 
  if (clk==1'b1) begin // Writing the file
    $fwrite(f_o,"%6d %7d     %b     %b       %h            %h     %b       %h            %h\n",
             $time,clk_cnt,reset,FM_L1L2XX_L3PHIC_dataarray_data_V_enb, FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr, FM_L1L2XX_L3PHIC_dataarray_data_V_dout,
                                 FM_L5L6XX_L3PHIC_dataarray_data_V_enb, FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr, FM_L5L6XX_L3PHIC_dataarray_data_V_dout);
    clk_cnt = clk_cnt+1;
  end
end

// Print to stdout
`define DISP0 "\ttime, clk_cnt, reset, TPROJ_L3PHIC_dataarray_data_V_wea, TPROJ_L3PHIC_dataarray_data_V_writeaddr[0], TPROJ_L3PHIC_dataarray_data_V_din[0]"
`define MON0  "%d, %d, %b,   %h,   %h,   %h", \
              $time, clk_cnt, reset, \
              {TPROJ_L3PHIC_dataarray_data_V_wea[7], TPROJ_L3PHIC_dataarray_data_V_wea[6], TPROJ_L3PHIC_dataarray_data_V_wea[5], TPROJ_L3PHIC_dataarray_data_V_wea[4], TPROJ_L3PHIC_dataarray_data_V_wea[3], TPROJ_L3PHIC_dataarray_data_V_wea[2], TPROJ_L3PHIC_dataarray_data_V_wea[1], TPROJ_L3PHIC_dataarray_data_V_wea[0]}, \
              TPROJ_L3PHIC_dataarray_data_V_writeaddr[0], TPROJ_L3PHIC_dataarray_data_V_din[0]
`define DISP1 "\ttime, clk_cnt, reset, \
FM_L1L2XX_L3PHIC_dataarray_data_V_enb, FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr, FM_L1L2XX_L3PHIC_dataarray_data_V_dout, \
FM_L5L6XX_L3PHIC_dataarray_data_V_enb, FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr, FM_L5L6XX_L3PHIC_dataarray_data_V_dout"
`define MON1  "%d, %d, %b,   %b, %h, %h,   %b, %h, %h", \
              $time, clk_cnt, reset, FM_L1L2XX_L3PHIC_dataarray_data_V_enb, FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr, FM_L1L2XX_L3PHIC_dataarray_data_V_dout, \
                                     FM_L5L6XX_L3PHIC_dataarray_data_V_enb, FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr, FM_L5L6XX_L3PHIC_dataarray_data_V_dout
generate
if (`DEBUG==1) begin
  initial  begin
   $display(`DISP0); 
   $monitor(`MON0); 
   $display(`DISP1); 
   $monitor(`MON1); 
   //#500   $finish; // Finish simulation after x time units
  end 
end
else begin
  initial begin
    $display(`DISP1);
    //#5000  $finish; // Finish simulation after x time units
  end
  always begin
    #c_CLK  //if (vld_out) begin
              $display(`MON1); 
            //end
  end
end
endgenerate

// File read for inputs (from memory .dat files)
always begin
  #(c_CLK/2)  if (clk==1'b1) begin // Reading the file
    for (int i = 0; i <= 7; i++) begin
      fgets_rtn = $fscanf(f_i[i], "%h\n", TPROJ_L3PHIC_dataarray_data_V_din[i]);
      TPROJ_L3PHIC_dataarray_data_V_wea [7:0] = '{default:1};
      if (clk_cnt > 1) begin // Wait one clk
        TPROJ_L3PHIC_dataarray_data_V_writeaddr[i] = TPROJ_L3PHIC_dataarray_data_V_writeaddr[i] + 1;
      end
    end
    
  end
end
// Periodic test patterns
always begin
  #(c_CLK/2)  if (clk==1'b1 & FM_L1L2XX_L3PHIC_dataarray_data_V_enb==1'b1) begin // Writing the file
                FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr = FM_L1L2XX_L3PHIC_dataarray_data_V_readaddr+1;
              end
              if (clk==1'b1 & FM_L5L6XX_L3PHIC_dataarray_data_V_enb==1'b1) begin // Writing the file
                FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr = FM_L5L6XX_L3PHIC_dataarray_data_V_readaddr+1;
              end
end
// Periodic events rising edge
always @(posedge clk) begin
  if (reset) en_proc = 1'b0;
  else       en_proc = 1'b1;
end
//Rest of testbench code after this line 
initial begin
  clk   = 1'b0;
  reset = 1'b1;
  en_proc = 1'b1;
  bx_in_ProjectionRouter = 3'b110;
  #(c_CLK/2)
  #(c_CLK*9)    reset = 1'b0;
  #(c_CLK*10)   FM_L1L2XX_L3PHIC_dataarray_data_V_enb = 1'b1;
                FM_L5L6XX_L3PHIC_dataarray_data_V_enb = 1'b1;
  #(c_CLK*125)  bx_in_ProjectionRouter <= bx_in_ProjectionRouter + 1'b1;
  #(c_CLK*50)   for (int i = 0; i <= 7; i++) begin
                  $fclose(f_i[i]);
                end
                $fclose(f_o); 
                $finish;
end




endmodule
