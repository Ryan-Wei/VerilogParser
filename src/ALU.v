module ALU(
    clk,
    rst,
    operandA,
    operandB,
    result,
    operation,
    operation_valid,
    busy
);

input           clk;
input           rst;
input[31:0]     operandA;
input[31:0]     operandB;
input[2:0]      operation;
input           operation_valid;

output[63:0]    result;
reg[63:0]       result;//√
output          busy;
reg             busy;//√

reg [31:0]      add_x;//√
reg [31:0]      add_y;//√
reg             signA;//√
reg             signB;//√
reg             cin;//√
reg             cout;//√
reg[31:0]       add_result;//加法器输出//√
reg             mul_n0;//乘法时添加一位//√
reg             busy_mul;//√
reg             busy_div;//√
reg             quotient;//上商√
reg[31:0]       mul_div_reg;//存放被乘数或者除数√
reg[31:0]       operandB_inner;//内部操作数B√
reg[5:0]        counter;//√
reg[1:0]        opcode_inner;//内部操作码，实现加减以及加0√

integer     add=3'b000;
integer     sub=3'b001;
integer     mul=3'b010;
integer     div=3'b011;


always @ (add_x,add_y,cin) //add_result cout
begin
    {cout,add_result}=add_x+add_y+cin;    
end

always @ (posedge clk or negedge rst) //counter
begin
    if(!rst)
        counter<=0;
    else
        if(busy)
            counter<=counter-6'b1;
        else if(operation==mul)
            counter<=6'b100001;
        else if(operation==div)
            counter<=6'b100001;   
end

always @ (posedge clk or negedge rst) //三个busy 相当于表示两种状态，busy作为输出
begin
    if(!rst)
    begin
        busy<=0;
        busy_div<=0;
        busy_mul<=0;
    end
    else 
    begin
    if(busy==1 && counter==6'b0)
    begin
        busy<=0;
        busy_div<=0;
        busy_mul<=0;
    end
    else if(busy==0)
    begin
        if(operation==mul)
        begin
            busy_mul<=1;
            busy_div<=0;
            busy<=1;
        end
        else if(operation==div)
        begin
            busy_div<=1;
            busy_mul<=0;
            busy<=1;
        end
    end
    end
end

always @ (posedge clk or negedge rst)//除法运算记录两个符号
begin
    if(!rst)
    begin
        signA<=0;
        signB<=0;
    end
    else if(operation==div)
    begin
        signA<=operandA[31];
        signB<=mul_div_reg[31];
    end
end

always @ (posedge clk or negedge rst) //result mul_n0
begin
    if(!rst)
        {result,mul_n0}<=65'b0;
    else
    begin
        if(operation==mul && busy==0)
            {result,mul_n0}<={32'b0,operandA,1'b0};

        else if (busy_mul==1)
            {result,mul_n0}<={add_result[31],add_result,result[31:0]};

        else if(operation==div && busy==0)//除法，此时不考虑mul_n0
            if(signA)
                result<={32'hffffffff,operandA};
            else
                result<={32'b0,operandA};

        else if(busy_div==1)
            if(counter==6'b000001)
                result<={add_result[31:0]+operandB_inner,result[30:0],quotient};
            else
                result<={add_result[30:0],result[31:0],quotient};
        

        else if(operation==add || operation==sub)
            result<={32'b0,add_result};
    end
end

always @ (result, busy, operandA)
begin
    if(busy)
        add_x=result[63:32];
    else
        add_x=operandA;
end

always @ (busy, operandB, mul_div_reg)
begin
    if(busy)
        operandB_inner=mul_div_reg;
    else
        operandB_inner=operandB;
end

always @ (posedge clk or negedge rst)
begin
    if(!rst)
        mul_div_reg<=32'b0;
    else
        if((operation==mul || operation==div) && busy==0)
            mul_div_reg=operandB;
end

always @ (add_result)
begin
    quotient=1'b0;
    if(busy_div)
    begin
        if(~(add_result[31]^signB))//同号
            quotient=1;
    end
end

always @ (busy, result, operation)
begin
    if(busy)
    begin
        if(busy_mul)//乘法
        begin
            if({result[0],mul_n0}==2'b11 || {result[0],mul_n0}==2'b00)
                opcode_inner=2'b00;//加0
            else if({result[0],mul_n0}==2'b01)
                opcode_inner=2'b01;//加
            else
                opcode_inner=2'b11;//减
        end

        else//除法
        begin
            if(counter==6'b000010)
                opcode_inner=2'b11;
            else
                begin
                if(add_result[31]^signB)//异号
                begin
                    opcode_inner=2'b01;//加
                end
                else//同号
                begin
                    opcode_inner=2'b11;//减
                end
            end
        end
    end

    else
    begin
        if(operation==add)
            opcode_inner=2'b01;//加
        else if(operation==sub)
            opcode_inner=2'b11;//减
        else
            opcode_inner=2'b00;
    end
end

always @ (opcode_inner, operandB_inner)//控制加法器
begin
    if (opcode_inner==2'b00)
    begin
        add_y=32'b0;
        cin=0;
    end
    else if (opcode_inner==2'b01)
    begin
        add_y=operandB_inner;
        cin=0;
    end
    else if (opcode_inner==2'b11)
    begin 
        add_y=~operandB_inner;
        cin=1;
    end
    else
    begin
        add_y=32'b0;
        cin=1;
    end
end


endmodule
